#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tg3_firmware_hdr {int /*<<< orphan*/  len; } ;
struct tg3 {int fw_len; TYPE_1__* fw; } ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int TG3_FW_HDR_LEN ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tg3_fw_data_len(struct tg3 *tp,
			   const struct tg3_firmware_hdr *fw_hdr)
{
	int fw_len;

	/* Non fragmented firmware have one firmware header followed by a
	 * contiguous chunk of data to be written. The length field in that
	 * header is not the length of data to be written but the complete
	 * length of the bss. The data length is determined based on
	 * tp->fw->size minus headers.
	 *
	 * Fragmented firmware have a main header followed by multiple
	 * fragments. Each fragment is identical to non fragmented firmware
	 * with a firmware header followed by a contiguous chunk of data. In
	 * the main header, the length field is unused and set to 0xffffffff.
	 * In each fragment header the length is the entire size of that
	 * fragment i.e. fragment data + header length. Data length is
	 * therefore length field in the header minus TG3_FW_HDR_LEN.
	 */
	if (tp->fw_len == 0xffffffff)
		fw_len = be32_to_cpu(fw_hdr->len);
	else
		fw_len = tp->fw->size;

	return (fw_len - TG3_FW_HDR_LEN) / sizeof(u32);
}