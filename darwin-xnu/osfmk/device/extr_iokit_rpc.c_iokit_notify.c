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
typedef  int /*<<< orphan*/  mach_no_senders_notification_t ;
struct TYPE_3__ {int msgh_id; } ;
typedef  TYPE_1__ mach_msg_header_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  MACH_NOTIFY_DEAD_NAME 132 
#define  MACH_NOTIFY_NO_SENDERS 131 
#define  MACH_NOTIFY_PORT_DELETED 130 
#define  MACH_NOTIFY_PORT_DESTROYED 129 
#define  MACH_NOTIFY_SEND_ONCE 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  iokit_no_senders (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

boolean_t
iokit_notify( mach_msg_header_t * msg )
{
    switch (msg->msgh_id) {
        case MACH_NOTIFY_NO_SENDERS:
            iokit_no_senders((mach_no_senders_notification_t *) msg);
            return TRUE;

        case MACH_NOTIFY_PORT_DELETED:
        case MACH_NOTIFY_PORT_DESTROYED:
        case MACH_NOTIFY_SEND_ONCE:
        case MACH_NOTIFY_DEAD_NAME:
        default:
            printf("iokit_notify: strange notification %d\n", msg->msgh_id);
            return FALSE;
    }
}