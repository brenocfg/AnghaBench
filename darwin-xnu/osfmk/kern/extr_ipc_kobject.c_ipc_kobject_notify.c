#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_22__ {int /*<<< orphan*/  RetCode; } ;
typedef  TYPE_2__ mig_reply_error_t ;
typedef  int /*<<< orphan*/  mach_port_mscount_t ;
struct TYPE_23__ {int /*<<< orphan*/  not_count; } ;
typedef  TYPE_3__ mach_no_senders_notification_t ;
struct TYPE_24__ {int /*<<< orphan*/  msgh_sender; int /*<<< orphan*/  msgh_audit; } ;
typedef  TYPE_4__ mach_msg_max_trailer_t ;
struct TYPE_25__ {int msgh_id; int /*<<< orphan*/  msgh_remote_port; scalar_t__ msgh_size; } ;
typedef  TYPE_5__ mach_msg_header_t ;
typedef  TYPE_6__* ipc_port_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_21__ {int /*<<< orphan*/  imq_seqno; } ;
struct TYPE_26__ {TYPE_1__ ip_messages; int /*<<< orphan*/  ip_mscount; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  IKOT_AU_SESSIONPORT 145 
#define  IKOT_FILEPORT 144 
#define  IKOT_IOKIT_CONNECT 143 
#define  IKOT_IOKIT_IDENT 142 
#define  IKOT_IOKIT_OBJECT 141 
#define  IKOT_NAMED_ENTRY 140 
#define  IKOT_SEMAPHORE 139 
#define  IKOT_TASK 138 
#define  IKOT_TASK_RESUME 137 
#define  IKOT_UPL 136 
#define  IKOT_VOUCHER 135 
#define  IKOT_VOUCHER_ATTR_CONTROL 134 
#define  IKOT_WORK_INTERVAL 133 
 int /*<<< orphan*/  KERNEL_AUDIT_TOKEN ; 
 int /*<<< orphan*/  KERNEL_SECURITY_TOKEN ; 
#define  MACH_NOTIFY_DEAD_NAME 132 
#define  MACH_NOTIFY_NO_SENDERS 131 
#define  MACH_NOTIFY_PORT_DELETED 130 
#define  MACH_NOTIFY_PORT_DESTROYED 129 
#define  MACH_NOTIFY_SEND_ONCE 128 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  MIG_NO_REPLY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  audit_session_nosenders (TYPE_5__*) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fileport_notify (TYPE_5__*) ; 
 int /*<<< orphan*/  iokit_notify (TYPE_5__*) ; 
 int ip_kotype (TYPE_6__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_6__*) ; 
 int /*<<< orphan*/  ipc_port_destroy (TYPE_6__*) ; 
 int /*<<< orphan*/  ipc_voucher_attr_control_notify (TYPE_5__*) ; 
 int /*<<< orphan*/  ipc_voucher_notify (TYPE_5__*) ; 
 int /*<<< orphan*/  semaphore_notify (TYPE_5__*) ; 
 int /*<<< orphan*/  task_port_notify (TYPE_5__*) ; 
 int /*<<< orphan*/  task_suspension_notify (TYPE_5__*) ; 
 int /*<<< orphan*/  upl_no_senders (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_interval_port_notify (TYPE_5__*) ; 

boolean_t
ipc_kobject_notify(
	mach_msg_header_t *request_header,
	mach_msg_header_t *reply_header)
{
	mach_msg_max_trailer_t * trailer;
	ipc_port_t port = (ipc_port_t) request_header->msgh_remote_port;

	((mig_reply_error_t *) reply_header)->RetCode = MIG_NO_REPLY;

	trailer = (mach_msg_max_trailer_t *)
	          ((vm_offset_t)request_header + request_header->msgh_size);

	/*
	 * The kobject notification is privileged and can change the
	 * refcount on kernel-internal objects - make sure
	 * that the message wasn't faked!
	 */
	if (0 != bcmp(&trailer->msgh_audit, &KERNEL_AUDIT_TOKEN,
			sizeof(trailer->msgh_audit))) {
		return FALSE;
	}
	if (0 != bcmp(&trailer->msgh_sender, &KERNEL_SECURITY_TOKEN,
			sizeof(trailer->msgh_sender))) {
		return FALSE;
	}

	switch (request_header->msgh_id) {
		case MACH_NOTIFY_NO_SENDERS:
			switch (ip_kotype(port)) {
			case IKOT_VOUCHER:
				ipc_voucher_notify(request_header);
				return TRUE;

			case IKOT_VOUCHER_ATTR_CONTROL:
				ipc_voucher_attr_control_notify(request_header);
				return TRUE;

			case IKOT_SEMAPHORE:
				semaphore_notify(request_header);
				return TRUE;

			case IKOT_TASK:
				task_port_notify(request_header);
				return TRUE;
				
			case IKOT_NAMED_ENTRY:
				ip_lock(port);

				/*
				 * Bring the sequence number and mscount in
				 * line with ipc_port_destroy assertion.
				 */
				port->ip_mscount = 0;
				port->ip_messages.imq_seqno = 0;
				ipc_port_destroy(port); /* releases lock */
				return TRUE;

			case IKOT_UPL:
				upl_no_senders(
					request_header->msgh_remote_port, 
					(mach_port_mscount_t) 
					((mach_no_senders_notification_t *) 
					 request_header)->not_count);
				reply_header->msgh_remote_port = MACH_PORT_NULL;
				return TRUE;

#if	CONFIG_AUDIT
			case IKOT_AU_SESSIONPORT:
				audit_session_nosenders(request_header);
				return TRUE;
#endif
			case IKOT_FILEPORT:
				fileport_notify(request_header);
				return TRUE;

			case IKOT_WORK_INTERVAL:
				work_interval_port_notify(request_header);
				return TRUE;

			}
		break;

		case MACH_NOTIFY_PORT_DELETED:
		case MACH_NOTIFY_PORT_DESTROYED:
		case MACH_NOTIFY_SEND_ONCE:
		case MACH_NOTIFY_DEAD_NAME:
		break;

		default:
		return FALSE;
	}
	switch (ip_kotype(port)) {

#ifdef IOKIT
		case IKOT_IOKIT_OBJECT:
		case IKOT_IOKIT_CONNECT:
		case IKOT_IOKIT_IDENT:
		{
                return iokit_notify(request_header);
		}
#endif
		case IKOT_TASK_RESUME:
		{
			return task_suspension_notify(request_header);
		}

		default:
                return FALSE;
        }
}