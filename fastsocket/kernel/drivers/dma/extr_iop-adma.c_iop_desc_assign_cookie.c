#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cookie; } ;
struct iop_adma_desc_slot {TYPE_2__ async_tx; } ;
struct TYPE_3__ {int cookie; } ;
struct iop_adma_chan {TYPE_1__ common; } ;
typedef  int dma_cookie_t ;

/* Variables and functions */

__attribute__((used)) static dma_cookie_t
iop_desc_assign_cookie(struct iop_adma_chan *iop_chan,
	struct iop_adma_desc_slot *desc)
{
	dma_cookie_t cookie = iop_chan->common.cookie;
	cookie++;
	if (cookie < 0)
		cookie = 1;
	iop_chan->common.cookie = desc->async_tx.cookie = cookie;
	return cookie;
}