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
typedef  int /*<<< orphan*/  BlockDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  blockdsp_init_mmi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blockdsp_init_msa (int /*<<< orphan*/ *) ; 

void ff_blockdsp_init_mips(BlockDSPContext *c)
{
#if HAVE_MMI
    blockdsp_init_mmi(c);
#endif /* HAVE_MMI */
#if HAVE_MSA
    blockdsp_init_msa(c);
#endif  // #if HAVE_MSA
}