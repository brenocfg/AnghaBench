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
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDAC (int) ; 
 int /*<<< orphan*/  CDSA_U (int) ; 
 int /*<<< orphan*/  CPC (int) ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_is_omap15xx () ; 
 int dma_read (int /*<<< orphan*/ ) ; 

dma_addr_t omap_get_dma_dst_pos(int lch)
{
	dma_addr_t offset = 0;

	if (cpu_is_omap15xx())
		offset = dma_read(CPC(lch));
	else
		offset = dma_read(CDAC(lch));

	/*
	 * omap 3.2/3.3 erratum: sometimes 0 is returned if CSAC/CDAC is
	 * read before the DMA controller finished disabling the channel.
	 */
	if (!cpu_is_omap15xx() && offset == 0)
		offset = dma_read(CDAC(lch));

	if (cpu_class_is_omap1())
		offset |= (dma_read(CDSA_U(lch)) << 16);

	return offset;
}