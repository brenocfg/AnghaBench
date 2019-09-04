#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* mnl_msg_t ;
typedef  int /*<<< orphan*/  ipc_kmsg_t ;
struct TYPE_4__ {int cmd; } ;

/* Variables and functions */
#define  FLIPC_CMD_ACKMESSAGE 129 
#define  FLIPC_CMD_NAKMESSAGE 128 
 int /*<<< orphan*/  ipc_kmsg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnl_msg_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
flipc_msg_free(mnl_msg_t    msg,
               uint32_t     flags)
{
    switch (msg->cmd) {
        case FLIPC_CMD_ACKMESSAGE:  // Flipc msg is a kmsg in disguise...
        case FLIPC_CMD_NAKMESSAGE:  // Convert back to kmsg for disposal
            ipc_kmsg_free(*(ipc_kmsg_t*)((vm_offset_t)msg-sizeof(vm_offset_t)));
            break;

        default:    // Flipc msg is not a kmsg in disguise; dispose of normally
            mnl_msg_free(msg, flags);
            break;
    }
}