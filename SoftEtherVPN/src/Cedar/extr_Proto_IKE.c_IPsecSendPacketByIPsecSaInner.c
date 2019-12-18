#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_18__ {int /*<<< orphan*/  HashSize; } ;
struct TYPE_17__ {scalar_t__* Buf; } ;
struct TYPE_16__ {int ServerPort; int ClientPort; int StartQuickModeAsSoon; int /*<<< orphan*/  ClientIP; int /*<<< orphan*/  ServerIP; } ;
struct TYPE_15__ {scalar_t__* NextIv; int /*<<< orphan*/  Key; scalar_t__* Iv; } ;
struct TYPE_13__ {scalar_t__ CapsuleMode; scalar_t__ LifeKilobytes; TYPE_1__* Crypto; TYPE_7__* Hash; } ;
struct TYPE_14__ {int Spi; int CurrentSeqNo; int TotalSize; int StartQM_FlagSet; TYPE_2__ TransformSetting; scalar_t__* EspIv; int /*<<< orphan*/  HashKey; int /*<<< orphan*/  CryptoKey; TYPE_5__* IkeClient; } ;
struct TYPE_12__ {int BlockSize; } ;
typedef  TYPE_3__ IPSECSA ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_4__ IKE_CRYPTO_PARAM ;
typedef  TYPE_5__ IKE_CLIENT ;
typedef  TYPE_6__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_6__*) ; 
 int IKE_ESP_HASH_SIZE ; 
 int IKE_MAX_HASH_SIZE ; 
 scalar_t__ IKE_P2_CAPSULE_TRANSPORT ; 
 scalar_t__ IKE_P2_CAPSULE_TUNNEL ; 
 int /*<<< orphan*/  IKE_UDP_TYPE_ESP ; 
 int IPSEC_PORT_IPSEC_ESP_RAW ; 
 TYPE_6__* IkeEncrypt (scalar_t__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  IkeHMac (TYPE_7__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  IkeSendUdpPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 scalar_t__* Malloc (int) ; 
 int /*<<< orphan*/  WRITE_UINT (scalar_t__*,int) ; 

void IPsecSendPacketByIPsecSaInner(IKE_SERVER *ike, IPSECSA *sa, UCHAR *data, UINT data_size, UCHAR protocol_id)
{
	UINT esp_size;
	UINT encrypted_payload_size;
	UCHAR *esp;
	UINT i;
	UINT size_of_padding;
	IKE_CRYPTO_PARAM cp;
	BUF *enc;
	IKE_CLIENT *c;
	// Validate arguments
	if (ike == NULL || sa == NULL || data == NULL || data_size == 0)
	{
		return;
	}

	c = sa->IkeClient;
	if (c == NULL)
	{
		return;
	}

	// Calculate the payload size after encryption
	encrypted_payload_size = data_size + 2;
	if ((encrypted_payload_size % sa->TransformSetting.Crypto->BlockSize) != 0)
	{
		encrypted_payload_size = ((encrypted_payload_size / sa->TransformSetting.Crypto->BlockSize) + 1) * sa->TransformSetting.Crypto->BlockSize;
	}
	size_of_padding = encrypted_payload_size - data_size - 2;

	// Calculate the size of the ESP packet
	esp_size = sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize + encrypted_payload_size + IKE_ESP_HASH_SIZE;

	// Build the ESP packet
	esp = Malloc(esp_size + IKE_MAX_HASH_SIZE);

	// SPI
	WRITE_UINT(esp, sa->Spi);

	// Sequence number
	sa->CurrentSeqNo++;
	WRITE_UINT(esp + sizeof(UINT), sa->CurrentSeqNo);

	// IV
	Copy(esp + sizeof(UINT) * 2, sa->EspIv, sa->TransformSetting.Crypto->BlockSize);

	// Payload data
	Copy(esp + sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize, data, data_size);

	// Padding
	for (i = 0;i < size_of_padding;i++)
	{
		esp[sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize + data_size + i] = (UCHAR)(i + 1);
	}

	// Padding length
	esp[sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize + data_size + size_of_padding] = (UCHAR)size_of_padding;

	// Next header number
	esp[sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize + data_size + size_of_padding + 1] = protocol_id;

	// Encryption
	Copy(cp.Iv, sa->EspIv, sa->TransformSetting.Crypto->BlockSize);
	cp.Key = sa->CryptoKey;

	enc = IkeEncrypt(esp + sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize, encrypted_payload_size, &cp);
	if (enc != NULL)
	{
		bool start_qm = false;
		UINT server_port = c->ServerPort;
		UINT client_port = c->ClientPort;

		// Overwrite the encrypted result
		Copy(esp + sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize, enc->Buf, encrypted_payload_size);

		FreeBuf(enc);

		// Calculate the HMAC
		IkeHMac(sa->TransformSetting.Hash,
			esp + sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize + encrypted_payload_size,
			sa->HashKey,
			sa->TransformSetting.Hash->HashSize,
			esp,
			sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize + encrypted_payload_size);

		//*(UCHAR *)(esp + sizeof(UINT) * 2 + sa->TransformSetting.Crypto->BlockSize + encrypted_payload_size) = 0xff;

		if (sa->TransformSetting.CapsuleMode == IKE_P2_CAPSULE_TRANSPORT ||
			sa->TransformSetting.CapsuleMode == IKE_P2_CAPSULE_TUNNEL)
		{
			server_port = client_port = IPSEC_PORT_IPSEC_ESP_RAW;
		}

		// Add the completed packet to the transmission list
		IkeSendUdpPacket(ike, IKE_UDP_TYPE_ESP, &c->ServerIP, server_port, &c->ClientIP, client_port,
			esp, esp_size);

		// Feedback the IV
		Copy(sa->EspIv, cp.NextIv, sa->TransformSetting.Crypto->BlockSize);

		sa->TotalSize += esp_size;

		if (sa->CurrentSeqNo >= 0xf0000000)
		{
			start_qm = true;
		}

		if (sa->TransformSetting.LifeKilobytes != 0)
		{
			UINT64 hard_size = (UINT64)sa->TransformSetting.LifeKilobytes * (UINT64)1000;
			UINT64 soft_size = hard_size * (UINT64)2 / (UINT64)3;

			if (sa->TotalSize >= soft_size)
			{
				start_qm = true;
			}
		}

		if (start_qm)
		{
			if (sa->StartQM_FlagSet == false)
			{
				sa->StartQM_FlagSet = true;
				c->StartQuickModeAsSoon = true;
			}
		}
	}
	else
	{
		// Encryption failure
		Free(esp);
	}
}