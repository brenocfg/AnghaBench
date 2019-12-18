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
typedef  int /*<<< orphan*/  controller_t ;
typedef  int /*<<< orphan*/  controller_local_param_t ;
struct TYPE_2__ {int /*<<< orphan*/  packet_parser; int /*<<< orphan*/  packet_factory; int /*<<< orphan*/  hci; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 TYPE_1__ controller_param ; 
 int /*<<< orphan*/ * controller_param_ptr ; 
 int /*<<< orphan*/  hci_layer_get_interface () ; 
 int /*<<< orphan*/  hci_packet_factory_get_interface () ; 
 int /*<<< orphan*/  hci_packet_parser_get_interface () ; 
 int /*<<< orphan*/  const interface ; 
 scalar_t__ osi_calloc (int) ; 

const controller_t *controller_get_interface(void)
{
    static bool loaded = false;
    if (!loaded) {
        loaded = true;
#if (BT_BLE_DYNAMIC_ENV_MEMORY == TRUE)
        controller_param_ptr = (controller_local_param_t *)osi_calloc(sizeof(controller_local_param_t));
        assert(controller_param_ptr);
#endif
        controller_param.hci = hci_layer_get_interface();
        controller_param.packet_factory = hci_packet_factory_get_interface();
        controller_param.packet_parser = hci_packet_parser_get_interface();
    }

    return &interface;
}