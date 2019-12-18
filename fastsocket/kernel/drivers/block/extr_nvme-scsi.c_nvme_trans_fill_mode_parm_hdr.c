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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int RESERVED_FIELD ; 
 int SNTI_INTERNAL_ERROR ; 
 int SNTI_TRANSLATION_SUCCESS ; 

__attribute__((used)) static int nvme_trans_fill_mode_parm_hdr(u8 *resp, int len, u8 cdb10, u8 llbaa,
					u16 mode_data_length, u16 blk_desc_len)
{
	/* Quick check to make sure I don't stomp on my own memory... */
	if ((cdb10 && len < 8) || (!cdb10 && len < 4))
		return SNTI_INTERNAL_ERROR;

	if (cdb10) {
		resp[0] = (mode_data_length & 0xFF00) >> 8;
		resp[1] = (mode_data_length & 0x00FF);
		/* resp[2] and [3] are zero */
		resp[4] = llbaa;
		resp[5] = RESERVED_FIELD;
		resp[6] = (blk_desc_len & 0xFF00) >> 8;
		resp[7] = (blk_desc_len & 0x00FF);
	} else {
		resp[0] = (mode_data_length & 0x00FF);
		/* resp[1] and [2] are zero */
		resp[3] = (blk_desc_len & 0x00FF);
	}

	return SNTI_TRANSLATION_SUCCESS;
}