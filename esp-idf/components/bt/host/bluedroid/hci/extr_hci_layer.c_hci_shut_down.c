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
struct TYPE_4__ {int /*<<< orphan*/  (* close ) () ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* cleanup ) () ;} ;

/* Variables and functions */
 TYPE_2__* hal ; 
 int hci_host_startup_flag ; 
 int /*<<< orphan*/ * hci_host_thread ; 
 int /*<<< orphan*/  hci_layer_deinit_env () ; 
 int /*<<< orphan*/  osi_thread_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* packet_fragmenter ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

void hci_shut_down(void)
{
    hci_host_startup_flag  = false;
    hci_layer_deinit_env();

    packet_fragmenter->cleanup();

    //low_power_manager->cleanup();
    hal->close();

    osi_thread_free(hci_host_thread);
    hci_host_thread = NULL;
}