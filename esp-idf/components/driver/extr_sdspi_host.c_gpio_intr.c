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
struct TYPE_2__ {int /*<<< orphan*/  gpio_int; int /*<<< orphan*/  semphr_int; } ;
typedef  TYPE_1__ slot_info_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_intr_disable (int /*<<< orphan*/ ) ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  portYIELD_FROM_ISR () ; 
 int /*<<< orphan*/  xSemaphoreGiveFromISR (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void gpio_intr(void* arg)
{
    BaseType_t awoken = pdFALSE;
    slot_info_t* slot = (slot_info_t*)arg;
    xSemaphoreGiveFromISR(slot->semphr_int, &awoken);
    gpio_intr_disable(slot->gpio_int);
    if (awoken) {
        portYIELD_FROM_ISR();
    }
}