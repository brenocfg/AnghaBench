#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* dma_regs; } ;
typedef  TYPE_3__ emac_hal_context_t ;
struct TYPE_5__ {scalar_t__ sw_rst; } ;
struct TYPE_6__ {TYPE_1__ dmabusmode; } ;

/* Variables and functions */

bool emac_hal_is_reset_done(emac_hal_context_t *hal)
{
    return hal->dma_regs->dmabusmode.sw_rst ? false : true;
}