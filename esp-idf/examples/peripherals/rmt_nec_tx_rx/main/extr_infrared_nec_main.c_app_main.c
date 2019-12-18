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
 int /*<<< orphan*/  rmt_example_nec_rx_task ; 
 int /*<<< orphan*/  rmt_example_nec_tx_task ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void app_main(void)
{
    xTaskCreate(rmt_example_nec_rx_task, "rmt_nec_rx_task", 2048, NULL, 10, NULL);
    xTaskCreate(rmt_example_nec_tx_task, "rmt_nec_tx_task", 2048, NULL, 10, NULL);
}