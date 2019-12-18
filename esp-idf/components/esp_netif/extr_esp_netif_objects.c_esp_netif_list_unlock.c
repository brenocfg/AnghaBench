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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ s_esp_netif_counter ; 
 int /*<<< orphan*/ * s_list_lock ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ *) ; 

void esp_netif_list_unlock(void)
{
    assert(s_list_lock);
    xSemaphoreGive(s_list_lock);
    if (s_esp_netif_counter == 0) {
        vQueueDelete(s_list_lock);
        s_list_lock = NULL;
    }
}