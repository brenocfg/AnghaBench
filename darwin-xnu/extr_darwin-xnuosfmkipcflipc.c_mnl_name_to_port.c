#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mnl_name_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  TYPE_1__* flipc_port_t ;
struct TYPE_3__ {int /*<<< orphan*/  lport; } ;

/* Variables and functions */
 scalar_t__ FPORT_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  IP_NULL ; 
 scalar_t__ MNL_NAME_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnl_obj_lookup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ipc_port_t mnl_name_to_port(mnl_name_t name)
{
    ipc_port_t lport = IP_NULL;

    if (MNL_NAME_VALID(name)) {
        flipc_port_t fport = (flipc_port_t)mnl_obj_lookup(name);
        if (FPORT_VALID(fport))
            lport = fport->lport;
    }
    return lport;
}