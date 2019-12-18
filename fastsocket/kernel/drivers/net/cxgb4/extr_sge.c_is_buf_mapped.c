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
 int RX_UNMAPPED_BUF ; 

__attribute__((used)) static inline bool is_buf_mapped(const struct rx_sw_desc *d)
{
	return !(d->dma_addr & RX_UNMAPPED_BUF);
}