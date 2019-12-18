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
 int /*<<< orphan*/  CSEI (int) ; 
 int /*<<< orphan*/  CSFI (int) ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 

void omap_set_dma_src_index(int lch, int eidx, int fidx)
{
	if (cpu_class_is_omap2())
		return;

	dma_write(eidx, CSEI(lch));
	dma_write(fidx, CSFI(lch));
}