#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  size_t mach_msg_type_number_t ;
typedef  scalar_t__ mach_msg_size_t ;
typedef  int /*<<< orphan*/  mach_msg_return_t ;
typedef  int /*<<< orphan*/  mach_msg_ool_ports_descriptor_t ;
typedef  int /*<<< orphan*/  mach_msg_ool_descriptor_t ;
struct TYPE_25__ {int /*<<< orphan*/  msgh_size; } ;
typedef  TYPE_3__ mach_msg_header_t ;
struct TYPE_23__ {int type; } ;
struct TYPE_26__ {TYPE_1__ type; } ;
typedef  TYPE_4__ mach_msg_descriptor_t ;
struct TYPE_27__ {size_t msgh_descriptor_count; } ;
typedef  TYPE_5__ mach_msg_body_t ;
typedef  int /*<<< orphan*/  mach_msg_base_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_6__* ipc_kmsg_t ;
typedef  int boolean_t ;
struct TYPE_28__ {TYPE_3__* ikm_header; } ;
struct TYPE_24__ {scalar_t__ max_offset; } ;

/* Variables and functions */
 TYPE_5__* MACH_MSG_BODY_NULL ; 
 TYPE_4__* MACH_MSG_DESCRIPTOR_NULL ; 
#define  MACH_MSG_OOL_DESCRIPTOR 131 
#define  MACH_MSG_OOL_PORTS_DESCRIPTOR 130 
#define  MACH_MSG_OOL_VOLATILE_DESCRIPTOR 129 
#define  MACH_MSG_PORT_DESCRIPTOR 128 
 int /*<<< orphan*/  MACH_MSG_SUCCESS ; 
 scalar_t__ VM_MAX_ADDRESS ; 
 TYPE_4__* ipc_kmsg_copyout_ool_descriptor (int /*<<< orphan*/ *,TYPE_4__*,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ipc_kmsg_copyout_ool_ports_descriptor (int /*<<< orphan*/ *,TYPE_4__*,int,TYPE_2__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ipc_kmsg_copyout_port_descriptor (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

mach_msg_return_t
ipc_kmsg_copyout_body(
    	ipc_kmsg_t		kmsg,
	ipc_space_t		space,
	vm_map_t		map,
	mach_msg_body_t		*slist)
{
    mach_msg_body_t 		*body;
    mach_msg_descriptor_t 	*kern_dsc, *user_dsc;
    mach_msg_descriptor_t	*saddr;
    mach_msg_type_number_t	dsc_count, sdsc_count;
    int i;
    mach_msg_return_t 		mr = MACH_MSG_SUCCESS;
    boolean_t 			is_task_64bit = (map->max_offset > VM_MAX_ADDRESS);

    body = (mach_msg_body_t *) (kmsg->ikm_header + 1);
    dsc_count = body->msgh_descriptor_count;
    kern_dsc = (mach_msg_descriptor_t *) (body + 1);
    /* Point user_dsc just after the end of all the descriptors */
    user_dsc = &kern_dsc[dsc_count];

    /* Do scatter list setup */
    if (slist != MACH_MSG_BODY_NULL) {
    panic("Scatter lists disabled");
	saddr = (mach_msg_descriptor_t *) (slist + 1);
	sdsc_count = slist->msgh_descriptor_count;
    }
    else {
	saddr = MACH_MSG_DESCRIPTOR_NULL;
	sdsc_count = 0;
    }

    /* Now process the descriptors */
    for (i = dsc_count-1; i >= 0; i--) {
        switch (kern_dsc[i].type.type) {

            case MACH_MSG_PORT_DESCRIPTOR: 
                user_dsc = ipc_kmsg_copyout_port_descriptor(&kern_dsc[i], user_dsc, space, &mr);
                break;
            case MACH_MSG_OOL_VOLATILE_DESCRIPTOR:
            case MACH_MSG_OOL_DESCRIPTOR : 
                user_dsc = ipc_kmsg_copyout_ool_descriptor(
                        (mach_msg_ool_descriptor_t *)&kern_dsc[i], user_dsc, is_task_64bit, map, &mr);
                break;
            case MACH_MSG_OOL_PORTS_DESCRIPTOR : 
                user_dsc = ipc_kmsg_copyout_ool_ports_descriptor(
                        (mach_msg_ool_ports_descriptor_t *)&kern_dsc[i], user_dsc, is_task_64bit, map, space, kmsg, &mr);
                break;
            default : {
                          panic("untyped IPC copyout body: invalid message descriptor");
                      }
        }
    }

    if(user_dsc != kern_dsc) {
        vm_offset_t dsc_adjust = (vm_offset_t)user_dsc - (vm_offset_t)kern_dsc;
        memmove((char *)((vm_offset_t)kmsg->ikm_header + dsc_adjust), kmsg->ikm_header, sizeof(mach_msg_base_t));
        kmsg->ikm_header = (mach_msg_header_t *)((vm_offset_t)kmsg->ikm_header + dsc_adjust);
        /* Update the message size for the smaller user representation */
        kmsg->ikm_header->msgh_size -= (mach_msg_size_t)dsc_adjust;
    }

    return mr;
}