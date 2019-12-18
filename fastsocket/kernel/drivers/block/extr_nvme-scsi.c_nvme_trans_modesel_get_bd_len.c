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
 size_t MODE_SELECT_10_BD_OFFSET ; 
 scalar_t__ MODE_SELECT_10_LLBAA_MASK ; 
 size_t MODE_SELECT_10_LLBAA_OFFSET ; 
 size_t MODE_SELECT_6_BD_OFFSET ; 

__attribute__((used)) static inline void nvme_trans_modesel_get_bd_len(u8 *parm_list, u8 cdb10,
						u16 *bd_len, u8 *llbaa)
{
	if (cdb10) {
		/* 10 Byte CDB */
		*bd_len = (parm_list[MODE_SELECT_10_BD_OFFSET] << 8) +
			parm_list[MODE_SELECT_10_BD_OFFSET + 1];
		*llbaa = parm_list[MODE_SELECT_10_LLBAA_OFFSET] &&
				MODE_SELECT_10_LLBAA_MASK;
	} else {
		/* 6 Byte CDB */
		*bd_len = parm_list[MODE_SELECT_6_BD_OFFSET];
	}
}