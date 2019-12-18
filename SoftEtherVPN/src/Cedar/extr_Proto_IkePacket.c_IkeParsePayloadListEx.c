#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  header ;
typedef  int USHORT ;
typedef  int UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_3__ {scalar_t__ NextPayload; int /*<<< orphan*/  PayloadSize; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IKE_PACKET_PAYLOAD ;
typedef  TYPE_1__ IKE_COMMON_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 scalar_t__ IKE_IS_SUPPORTED_PAYLOAD_TYPE (scalar_t__) ; 
 scalar_t__ IKE_PAYLOAD_NONE ; 
 int /*<<< orphan*/  IkeFreePayloadList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IkeParsePayload (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MemToBuf (void*,int) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int ReadBuf (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ReadBufFromBuf (int /*<<< orphan*/ *,int) ; 

LIST *IkeParsePayloadListEx(void *data, UINT size, UCHAR first_payload, UINT *total_read_size)
{
	LIST *o;
	BUF *b;
	UCHAR payload_type = first_payload;
	UINT total = 0;
	// Validate arguments
	if (data == NULL)
	{
		return NULL;
	}

	o = NewListFast(NULL);
	b = MemToBuf(data, size);

	while (payload_type != IKE_PAYLOAD_NONE)
	{
		// Read the common header
		IKE_COMMON_HEADER header;
		USHORT payload_size;
		BUF *payload_data;
		IKE_PACKET_PAYLOAD *pay;

		if (ReadBuf(b, &header, sizeof(header)) != sizeof(header))
		{
			Debug("ISAKMP: Broken Packet (Invalid Payload Size)\n");

LABEL_ERROR:
			// Header reading failure
			IkeFreePayloadList(o);
			o = NULL;

			break;
		}

		total += sizeof(header);

		// Get the payload size
		payload_size = Endian16(header.PayloadSize);

		if (payload_size < sizeof(header))
		{
			Debug("ISAKMP: Broken Packet (Invalid Payload Size)\n");
			goto LABEL_ERROR;
		}

		payload_size -= sizeof(header);

		// Read the payload data
		payload_data = ReadBufFromBuf(b, payload_size);
		if (payload_data == NULL)
		{
			// Data read failure
			Debug("ISAKMP: Broken Packet (Invalid Payload Data)\n");
			goto LABEL_ERROR;
		}

		total += payload_size;

		// Analyse the payload body
		if (IKE_IS_SUPPORTED_PAYLOAD_TYPE(payload_type))
		{
			// Supported payload type
			pay = IkeParsePayload(payload_type, payload_data);

			if (pay == NULL)
			{
				FreeBuf(payload_data);
				Debug("ISAKMP: Broken Packet (Payload Data Parse Failed)\n");
				goto LABEL_ERROR;
			}

			Add(o, pay);
		}
		else
		{
			// Unsupported payload type
			Debug("ISAKMP: Ignored Payload Type: %u\n", payload_type);
			pay = IkeParsePayload(payload_type, payload_data);

			if (pay == NULL)
			{
				FreeBuf(payload_data);
				Debug("ISAKMP: Broken Packet (Payload Data Parse Failed)\n");
				goto LABEL_ERROR;
			}

			Add(o, pay);
		}

		payload_type = header.NextPayload;

		FreeBuf(payload_data);
	}

	FreeBuf(b);

	if (total_read_size != NULL)
	{
		*total_read_size = total;
	}

	return o;
}