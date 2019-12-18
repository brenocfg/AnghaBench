#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_map_t ;
typedef  int /*<<< orphan*/  mach_msg_size_t ;
struct TYPE_9__ {int type; } ;
struct TYPE_12__ {TYPE_1__ type; } ;
typedef  TYPE_4__ mach_msg_descriptor_t ;
struct TYPE_13__ {int msgh_descriptor_count; } ;
typedef  TYPE_5__ mach_msg_body_t ;
typedef  TYPE_6__* ipc_kmsg_t ;
typedef  int boolean_t ;
struct TYPE_14__ {TYPE_2__* ikm_header; } ;
struct TYPE_11__ {scalar_t__ max_offset; } ;
struct TYPE_10__ {int msgh_bits; int /*<<< orphan*/  msgh_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_SIZE_ADJUSTMENT ; 
 scalar_t__ LEGACY_HEADER_SIZE_DELTA ; 
 int MACH_MSGH_BITS_COMPLEX ; 
#define  MACH_MSG_OOL_DESCRIPTOR 131 
#define  MACH_MSG_OOL_PORTS_DESCRIPTOR 130 
#define  MACH_MSG_OOL_VOLATILE_DESCRIPTOR 129 
#define  MACH_MSG_PORT_DESCRIPTOR 128 
 scalar_t__ VM_MAX_ADDRESS ; 

mach_msg_size_t
ipc_kmsg_copyout_size(
	ipc_kmsg_t		kmsg,
	vm_map_t		map)
{
    mach_msg_size_t		send_size;

    send_size = kmsg->ikm_header->msgh_size;

    boolean_t is_task_64bit = (map->max_offset > VM_MAX_ADDRESS);

#if defined(__LP64__)
	send_size -= LEGACY_HEADER_SIZE_DELTA;
#endif

    if (kmsg->ikm_header->msgh_bits & MACH_MSGH_BITS_COMPLEX) {

        mach_msg_body_t *body;
        mach_msg_descriptor_t *saddr, *eaddr;

        body = (mach_msg_body_t *) (kmsg->ikm_header + 1);
        saddr = (mach_msg_descriptor_t *) (body + 1);
        eaddr = saddr + body->msgh_descriptor_count;

        for ( ; saddr < eaddr; saddr++ ) {
            switch (saddr->type.type) {
                case MACH_MSG_OOL_DESCRIPTOR:
                case MACH_MSG_OOL_VOLATILE_DESCRIPTOR:
                case MACH_MSG_OOL_PORTS_DESCRIPTOR:
                    if(!is_task_64bit)
                        send_size -= DESC_SIZE_ADJUSTMENT;
                    break;
                case MACH_MSG_PORT_DESCRIPTOR:
                    send_size -= DESC_SIZE_ADJUSTMENT;
                    break;
                default:
                    break;
            }
        }
    }
    return send_size;
}