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
struct fw_packet {int /*<<< orphan*/ * header; } ;
struct fw_ohci {int /*<<< orphan*/  card; scalar_t__ config_rom; } ;

/* Variables and functions */
 int CONFIG_ROM_SIZE ; 
 int CSR_CONFIG_ROM ; 
 int HEADER_GET_DATA_LENGTH (int /*<<< orphan*/ ) ; 
 int HEADER_GET_TCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCODE_ADDRESS_ERROR ; 
 int /*<<< orphan*/  RCODE_COMPLETE ; 
 int /*<<< orphan*/  RCODE_TYPE_ERROR ; 
 scalar_t__ TCODE_IS_BLOCK_PACKET (int) ; 
 int /*<<< orphan*/  TCODE_IS_READ_REQUEST (int) ; 
 int /*<<< orphan*/  fw_core_handle_response (int /*<<< orphan*/ *,struct fw_packet*) ; 
 int /*<<< orphan*/  fw_fill_response (struct fw_packet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void handle_local_rom(struct fw_ohci *ohci,
			     struct fw_packet *packet, u32 csr)
{
	struct fw_packet response;
	int tcode, length, i;

	tcode = HEADER_GET_TCODE(packet->header[0]);
	if (TCODE_IS_BLOCK_PACKET(tcode))
		length = HEADER_GET_DATA_LENGTH(packet->header[3]);
	else
		length = 4;

	i = csr - CSR_CONFIG_ROM;
	if (i + length > CONFIG_ROM_SIZE) {
		fw_fill_response(&response, packet->header,
				 RCODE_ADDRESS_ERROR, NULL, 0);
	} else if (!TCODE_IS_READ_REQUEST(tcode)) {
		fw_fill_response(&response, packet->header,
				 RCODE_TYPE_ERROR, NULL, 0);
	} else {
		fw_fill_response(&response, packet->header, RCODE_COMPLETE,
				 (void *) ohci->config_rom + i, length);
	}

	fw_core_handle_response(&ohci->card, &response);
}