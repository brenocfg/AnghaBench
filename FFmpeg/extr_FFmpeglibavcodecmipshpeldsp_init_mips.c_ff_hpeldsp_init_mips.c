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
typedef  int /*<<< orphan*/  HpelDSPContext ;

/* Variables and functions */

void ff_hpeldsp_init_mips(HpelDSPContext *c, int flags)
{
#if HAVE_MMI
    ff_hpeldsp_init_mmi(c, flags);
#endif  // #if HAVE_MMI
#if HAVE_MSA
    ff_hpeldsp_init_msa(c, flags);
#endif  // #if HAVE_MSA
}