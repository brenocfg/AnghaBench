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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int MODE_SENSE_BLK_DESC_COUNT ; 
 scalar_t__ MODE_SENSE_BLK_DESC_ENABLED ; 

__attribute__((used)) static inline int nvme_trans_get_blk_desc_len(u8 dbd, u8 llbaa)
{
	if (dbd == MODE_SENSE_BLK_DESC_ENABLED) {
		/* SPC-4: len = 8 x Num_of_descriptors if llbaa = 0, 16x if 1 */
		return 8 * (llbaa + 1) * MODE_SENSE_BLK_DESC_COUNT;
	} else {
		return 0;
	}
}