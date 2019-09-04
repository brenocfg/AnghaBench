#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mnl_name_t ;
typedef  TYPE_5__* ipc_port_t ;
typedef  TYPE_6__* flipc_port_t ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_15__ {TYPE_4__ obj; } ;
struct TYPE_10__ {TYPE_6__* fport; } ;
struct TYPE_11__ {TYPE_1__ port; } ;
struct TYPE_12__ {TYPE_2__ data; } ;
struct TYPE_14__ {TYPE_3__ ip_messages; } ;

/* Variables and functions */
 scalar_t__ FPORT_VALID (TYPE_6__*) ; 
 scalar_t__ IP_VALID (TYPE_5__*) ; 
 int /*<<< orphan*/  MNL_NAME_NULL ; 

__attribute__((used)) static inline mnl_name_t mnl_name_from_port(ipc_port_t lport)
{
    mnl_name_t name = MNL_NAME_NULL;

    if (IP_VALID(lport)) {
        flipc_port_t fport = lport->ip_messages.data.port.fport;
        if (FPORT_VALID(fport))
            name = fport->obj.name;
    }
    return name;
}