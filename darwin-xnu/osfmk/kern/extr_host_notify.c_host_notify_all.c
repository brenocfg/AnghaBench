#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* queue_t ;
struct TYPE_22__ {TYPE_2__* prev; TYPE_1__* next; } ;
typedef  TYPE_3__ queue_head_t ;
typedef  int /*<<< orphan*/  mach_msg_size_t ;
struct TYPE_23__ {TYPE_6__* msgh_remote_port; int /*<<< orphan*/  msgh_id; void* msgh_voucher_port; void* msgh_local_port; int /*<<< orphan*/  msgh_bits; } ;
typedef  TYPE_5__ mach_msg_header_t ;
typedef  TYPE_6__* ipc_port_t ;
typedef  scalar_t__ ipc_kobject_t ;
typedef  TYPE_7__* host_notify_t ;
typedef  size_t host_flavor_t ;
struct TYPE_25__ {TYPE_6__* port; } ;
struct TYPE_24__ {scalar_t__ ip_kobject; } ;
struct TYPE_21__ {TYPE_3__* next; } ;
struct TYPE_20__ {TYPE_3__* prev; } ;

/* Variables and functions */
 scalar_t__ IKOT_HOST_NOTIFY ; 
 int /*<<< orphan*/  IKOT_NONE ; 
 int /*<<< orphan*/  IKO_NULL ; 
 TYPE_6__* IP_NULL ; 
 int /*<<< orphan*/  MACH_MSGH_BITS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MOVE_SEND_ONCE ; 
 void* MACH_PORT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dequeue (TYPE_3__*) ; 
 int /*<<< orphan*/  host_notify_lock ; 
 TYPE_3__* host_notify_queue ; 
 int /*<<< orphan*/ * host_notify_replyid ; 
 int /*<<< orphan*/  host_notify_zone ; 
 scalar_t__ ip_kotype (TYPE_6__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_6__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_6__*) ; 
 int /*<<< orphan*/  ipc_kobject_set_atomically (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_msg_send_from_kernel_proper (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  queue_init (TYPE_3__*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static void
host_notify_all(
	host_flavor_t		notify_type,
	mach_msg_header_t	*msg,
	mach_msg_size_t		msg_size)
{
	queue_t		notify_queue = &host_notify_queue[notify_type];

	lck_mtx_lock(&host_notify_lock);

	if (!queue_empty(notify_queue)) {
		queue_head_t		send_queue;
		host_notify_t		entry;

		send_queue = *notify_queue;
		queue_init(notify_queue);

		send_queue.next->prev = &send_queue;
		send_queue.prev->next = &send_queue;

		msg->msgh_bits =
		    MACH_MSGH_BITS_SET(MACH_MSG_TYPE_MOVE_SEND_ONCE, 0, 0, 0);
		msg->msgh_local_port = MACH_PORT_NULL;
		msg->msgh_voucher_port = MACH_PORT_NULL;
		msg->msgh_id = host_notify_replyid[notify_type];

		while ((entry = (host_notify_t)dequeue(&send_queue)) != NULL) {
			ipc_port_t		port;

			port = entry->port;
			assert(port != IP_NULL);

			ip_lock(port);
			assert(ip_kotype(port) == IKOT_HOST_NOTIFY);
			assert(port->ip_kobject == (ipc_kobject_t)entry);
			ipc_kobject_set_atomically(port, IKO_NULL, IKOT_NONE);
			ip_unlock(port);

			lck_mtx_unlock(&host_notify_lock);
			zfree(host_notify_zone, entry);

			msg->msgh_remote_port = port;

			(void) mach_msg_send_from_kernel_proper(msg, msg_size);

			lck_mtx_lock(&host_notify_lock);
		}
	}

	lck_mtx_unlock(&host_notify_lock);
}