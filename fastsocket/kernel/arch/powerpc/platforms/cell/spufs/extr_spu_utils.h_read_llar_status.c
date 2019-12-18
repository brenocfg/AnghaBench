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
 int /*<<< orphan*/  MFC_RdAtomicStat ; 
 int /*<<< orphan*/  spu_readch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void read_llar_status(void)
{
	/* Save, Step 17:
	 * Restore, Step 10:
	 *    Read the MFC_AtomicStat channel data.
	 */
	spu_readch(MFC_RdAtomicStat);
}