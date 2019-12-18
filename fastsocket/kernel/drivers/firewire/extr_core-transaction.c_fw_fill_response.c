#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct fw_packet {int* header; int header_length; size_t payload_length; scalar_t__ payload_bus; void* payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int HEADER_DATA_LENGTH (size_t) ; 
 int HEADER_DESTINATION (int) ; 
 int HEADER_EXTENDED_TCODE (int) ; 
 int HEADER_GET_DESTINATION (int) ; 
 int HEADER_GET_EXTENDED_TCODE (int) ; 
 int HEADER_GET_SOURCE (int) ; 
 int HEADER_GET_TCODE (int) ; 
 int HEADER_GET_TLABEL (int) ; 
 int HEADER_RCODE (int) ; 
 int HEADER_RETRY (int /*<<< orphan*/ ) ; 
 int HEADER_SOURCE (int) ; 
 int HEADER_TCODE (int) ; 
 int HEADER_TLABEL (int) ; 
 int /*<<< orphan*/  RETRY_1 ; 
#define  TCODE_LOCK_REQUEST 132 
#define  TCODE_READ_BLOCK_REQUEST 131 
#define  TCODE_READ_QUADLET_REQUEST 130 
 int TCODE_READ_QUADLET_RESPONSE ; 
#define  TCODE_WRITE_BLOCK_REQUEST 129 
#define  TCODE_WRITE_QUADLET_REQUEST 128 
 int TCODE_WRITE_RESPONSE ; 

void fw_fill_response(struct fw_packet *response, u32 *request_header,
		      int rcode, void *payload, size_t length)
{
	int tcode, tlabel, extended_tcode, source, destination;

	tcode          = HEADER_GET_TCODE(request_header[0]);
	tlabel         = HEADER_GET_TLABEL(request_header[0]);
	source         = HEADER_GET_DESTINATION(request_header[0]);
	destination    = HEADER_GET_SOURCE(request_header[1]);
	extended_tcode = HEADER_GET_EXTENDED_TCODE(request_header[3]);

	response->header[0] =
		HEADER_RETRY(RETRY_1) |
		HEADER_TLABEL(tlabel) |
		HEADER_DESTINATION(destination);
	response->header[1] =
		HEADER_SOURCE(source) |
		HEADER_RCODE(rcode);
	response->header[2] = 0;

	switch (tcode) {
	case TCODE_WRITE_QUADLET_REQUEST:
	case TCODE_WRITE_BLOCK_REQUEST:
		response->header[0] |= HEADER_TCODE(TCODE_WRITE_RESPONSE);
		response->header_length = 12;
		response->payload_length = 0;
		break;

	case TCODE_READ_QUADLET_REQUEST:
		response->header[0] |=
			HEADER_TCODE(TCODE_READ_QUADLET_RESPONSE);
		if (payload != NULL)
			response->header[3] = *(u32 *)payload;
		else
			response->header[3] = 0;
		response->header_length = 16;
		response->payload_length = 0;
		break;

	case TCODE_READ_BLOCK_REQUEST:
	case TCODE_LOCK_REQUEST:
		response->header[0] |= HEADER_TCODE(tcode + 2);
		response->header[3] =
			HEADER_DATA_LENGTH(length) |
			HEADER_EXTENDED_TCODE(extended_tcode);
		response->header_length = 16;
		response->payload = payload;
		response->payload_length = length;
		break;

	default:
		BUG();
		return;
	}

	response->payload_bus = 0;
}