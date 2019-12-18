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
typedef  int /*<<< orphan*/  hci_t ;

/* Variables and functions */
 int /*<<< orphan*/  hal ; 
 int /*<<< orphan*/  hci_hal_h4_get_interface () ; 
 int /*<<< orphan*/  init_layer_interface () ; 
 int /*<<< orphan*/  const interface ; 
 int /*<<< orphan*/  packet_fragmenter ; 
 int /*<<< orphan*/  packet_fragmenter_get_interface () ; 

const hci_t *hci_layer_get_interface(void)
{
    hal = hci_hal_h4_get_interface();
    packet_fragmenter = packet_fragmenter_get_interface();

    init_layer_interface();
    return &interface;
}