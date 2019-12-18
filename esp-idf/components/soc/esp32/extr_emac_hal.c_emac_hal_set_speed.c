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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {TYPE_2__* mac_regs; } ;
typedef  TYPE_3__ emac_hal_context_t ;
struct TYPE_5__ {int /*<<< orphan*/  fespeed; } ;
struct TYPE_6__ {TYPE_1__ gmacconfig; } ;

/* Variables and functions */

void emac_hal_set_speed(emac_hal_context_t *hal, uint32_t speed)
{
    hal->mac_regs->gmacconfig.fespeed = speed;
}