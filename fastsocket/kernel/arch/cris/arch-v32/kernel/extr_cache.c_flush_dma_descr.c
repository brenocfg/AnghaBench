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
struct dma_descr_data {scalar_t__ buf; scalar_t__ after; } ;

/* Variables and functions */
 int /*<<< orphan*/  cris_flush_cache_range (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  phys_to_virt (unsigned int) ; 

inline void flush_dma_descr(struct dma_descr_data *descr, int flush_buf)
{
	/* Flush descriptor to make sure we get correct in_eop and after. */
	asm volatile ("ftagd [%0]" :: "r" (descr));
	/* Flush buffer pointed out by descriptor. */
	if (flush_buf)
		cris_flush_cache_range(phys_to_virt((unsigned)descr->buf),
				(unsigned)(descr->after - descr->buf));
}