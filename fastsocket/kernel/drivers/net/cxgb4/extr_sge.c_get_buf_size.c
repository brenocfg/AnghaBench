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
struct rx_sw_desc {int dma_addr; } ;

/* Variables and functions */
 int FL_PG_ORDER ; 
 int PAGE_SIZE ; 
 int RX_LARGE_BUF ; 

__attribute__((used)) static inline int get_buf_size(const struct rx_sw_desc *d)
{
#if FL_PG_ORDER > 0
	return (d->dma_addr & RX_LARGE_BUF) ? (PAGE_SIZE << FL_PG_ORDER) :
					      PAGE_SIZE;
#else
	return PAGE_SIZE;
#endif
}