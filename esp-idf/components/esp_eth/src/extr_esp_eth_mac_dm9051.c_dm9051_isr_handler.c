#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rx_task_hdl; } ;
typedef  TYPE_1__ emac_dm9051_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  portYIELD_FROM_ISR () ; 
 int /*<<< orphan*/  vTaskNotifyGiveFromISR (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void dm9051_isr_handler(void *arg)
{
    emac_dm9051_t *emac = (emac_dm9051_t *)arg;
    BaseType_t high_task_wakeup = pdFALSE;
    /* notify dm9051 task */
    vTaskNotifyGiveFromISR(emac->rx_task_hdl, &high_task_wakeup);
    if (high_task_wakeup != pdFALSE) {
        portYIELD_FROM_ISR();
    }
}