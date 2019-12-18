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
 int /*<<< orphan*/  MFC_RdTagStat ; 
 int /*<<< orphan*/  spu_readch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void read_tag_status(void)
{
	/* Save, Step 16:
	 * Restore, Step 9:
	 *    Read the MFC_TagStat channel data.
	 */
	spu_readch(MFC_RdTagStat);
}