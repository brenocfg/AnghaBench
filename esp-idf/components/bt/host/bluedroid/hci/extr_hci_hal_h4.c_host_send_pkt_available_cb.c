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
 int /*<<< orphan*/  OSI_THREAD_MAX_TIMEOUT ; 
 int /*<<< orphan*/  hci_host_task_post (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void host_send_pkt_available_cb(void)
{
    //Controller rx cache buffer is ready for receiving new host packet
    //Just Call Host main thread task to process pending packets.
    hci_host_task_post(OSI_THREAD_MAX_TIMEOUT);
}