#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tag ;
typedef  int /*<<< orphan*/  op ;
typedef  int /*<<< orphan*/  data_packet_id ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_7__ {int Size; } ;
struct TYPE_6__ {scalar_t__ IvSize; scalar_t__ IsAeadCipher; } ;
struct TYPE_5__ {int* IvSend; int /*<<< orphan*/  Session; int /*<<< orphan*/  Server; TYPE_3__* CipherEncrypt; TYPE_4__* MdSend; } ;
typedef  TYPE_1__ OPENVPN_CHANNEL ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int*,...) ; 
 int /*<<< orphan*/  Free (int*) ; 
 int* Malloc (scalar_t__) ; 
 int OPENVPN_P_DATA_V1 ; 
 scalar_t__ OvsEncrypt (TYPE_3__*,TYPE_4__*,int*,int*,int*,int*,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  OvsSendPacketRawNow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  WRITE_UINT (int*,scalar_t__) ; 
 int* ZeroMalloc (scalar_t__) ; 

void OvsSendDataPacket(OPENVPN_CHANNEL *c, UCHAR key_id, UINT data_packet_id, void *data, UINT data_size)
{
	const UCHAR op = ((OPENVPN_P_DATA_V1 << 3) & 0xF8) | (key_id & 0x07);
	UCHAR *dest_data;
	UINT dest_size;
	// Validate arguments
	if (c == NULL || data == NULL || data_size == 0)
	{
		return;
	}

	// [ xxx ]		= unprotected
	// [ - xxx - ]	= authenticated
	// [ * xxx * ]	= encrypted and authenticated

	if (c->CipherEncrypt->IsAeadCipher)
	{
		// [ opcode ] [ - packet ID - ] [ TAG ] [ * packet payload * ]
		UCHAR tag[16];

		// Update variable part (packet ID) of IV
		WRITE_UINT(c->IvSend, data_packet_id);

		// Prepare a buffer to store the results
		dest_data = Malloc(sizeof(op) + sizeof(data_packet_id) + sizeof(tag) + data_size + 256);

		// Set data size to the maximum known
		dest_size = sizeof(op) + sizeof(data_packet_id) + sizeof(tag);

		// Write opcode
		dest_data[0] = op;

		// Write packet ID
		WRITE_UINT(dest_data + sizeof(op), data_packet_id);

		// Write encrypted payload
		dest_size += OvsEncrypt(c->CipherEncrypt, NULL, c->IvSend, tag, dest_data + dest_size, data, data_size, c->IvSend, sizeof(data_packet_id));

		// Write authentication tag
		Copy(dest_data + sizeof(op) + sizeof(data_packet_id), tag, sizeof(tag));
	}
	else
	{
		// [ opcode ] [ HMAC ] [ - IV - ] [ * packet ID * ] [ * packet payload * ]
		UINT encrypted_size = sizeof(data_packet_id) + data_size;
		UCHAR *encrypted_data = ZeroMalloc(encrypted_size);
		WRITE_UINT(encrypted_data, data_packet_id);
		Copy(encrypted_data + sizeof(data_packet_id), data, data_size);

		// Prepare a buffer to store the results
		dest_data = Malloc(sizeof(op) + c->MdSend->Size + c->CipherEncrypt->IvSize + encrypted_size + 256);

		// Set data size to the maximum known
		dest_size = sizeof(op);

		// Write opcode
		dest_data[0] = op;

		// Write IV, encrypted packet ID and payload
		dest_size += OvsEncrypt(c->CipherEncrypt, c->MdSend, c->IvSend, NULL, dest_data + sizeof(op), encrypted_data, encrypted_size, NULL, 0);

		Free(encrypted_data);

		// Update the IV
		Copy(c->IvSend, dest_data + dest_size - c->CipherEncrypt->IvSize, c->CipherEncrypt->IvSize);
	}

	OvsSendPacketRawNow(c->Server, c->Session, dest_data, dest_size);
}