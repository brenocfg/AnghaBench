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

/* Variables and functions */
 int /*<<< orphan*/  MFC_WrTagMask ; 
 int /*<<< orphan*/  spu_writech (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void set_tag_mask(void)
{
	unsigned int tag_mask = 1;

	/* Save, Step 5:
	 * Restore, Step 2:
	 *    Set the SPU_WrTagMsk channel to '01' to unmask
	 *    only tag group 0.
	 */
	spu_writech(MFC_WrTagMask, tag_mask);
}