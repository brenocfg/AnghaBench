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
struct etrax_dma_descr {int sw_len; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_etrax_cacherange (void*,int) ; 

void
prepare_rx_descriptor(struct etrax_dma_descr *desc)
{
	flush_etrax_cacherange((void *)desc->buf, desc->sw_len ? desc->sw_len : 65536);
}