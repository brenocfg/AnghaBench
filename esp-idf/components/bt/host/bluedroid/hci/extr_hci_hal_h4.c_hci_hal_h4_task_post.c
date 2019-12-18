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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  hci_h4_thread ; 
 int /*<<< orphan*/  hci_hal_h4_rx_handler ; 
 int osi_thread_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

bool hci_hal_h4_task_post(uint32_t timeout)
{
    return osi_thread_post(hci_h4_thread, hci_hal_h4_rx_handler, NULL, 1, timeout);
}