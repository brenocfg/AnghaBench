#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mq_attr {int /*<<< orphan*/  mq_curmsgs; int /*<<< orphan*/  mq_msgsize; int /*<<< orphan*/  mq_maxmsg; int /*<<< orphan*/  mq_flags; } ;
struct TYPE_13__ {int fd; int /*<<< orphan*/  flags; } ;
struct TYPE_22__ {int /*<<< orphan*/  effective; int /*<<< orphan*/  permitted; int /*<<< orphan*/  inheritable; } ;
struct TYPE_12__ {TYPE_9__ cap; int /*<<< orphan*/  pid; } ;
struct TYPE_21__ {int /*<<< orphan*/  mqdes; struct mq_attr mqstat; } ;
struct TYPE_20__ {int mqdes; int /*<<< orphan*/  sigev_signo; } ;
struct TYPE_18__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_19__ {TYPE_5__ abs_timeout; int /*<<< orphan*/  msg_prio; int /*<<< orphan*/  msg_len; int /*<<< orphan*/  mqdes; } ;
struct TYPE_16__ {int /*<<< orphan*/  mq_curmsgs; int /*<<< orphan*/  mq_msgsize; int /*<<< orphan*/  mq_maxmsg; int /*<<< orphan*/  mq_flags; } ;
struct TYPE_17__ {TYPE_3__ attr; int /*<<< orphan*/  mode; int /*<<< orphan*/  oflag; } ;
struct TYPE_15__ {int /*<<< orphan*/  perm_mode; int /*<<< orphan*/  perm_gid; int /*<<< orphan*/  perm_uid; int /*<<< orphan*/  qbytes; int /*<<< orphan*/  has_perm; int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  osid; } ;
struct TYPE_14__ {int nargs; int /*<<< orphan*/ * args; } ;
struct audit_context {int type; TYPE_11__ mmap; TYPE_10__ capset; TYPE_8__ mq_getsetattr; TYPE_7__ mq_notify; TYPE_6__ mq_sendrecv; TYPE_4__ mq_open; TYPE_2__ ipc; TYPE_1__ socketcall; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
#define  AUDIT_CAPSET 135 
#define  AUDIT_IPC 134 
 int AUDIT_IPC_SET_PERM ; 
#define  AUDIT_MMAP 133 
#define  AUDIT_MQ_GETSETATTR 132 
#define  AUDIT_MQ_NOTIFY 131 
#define  AUDIT_MQ_OPEN 130 
#define  AUDIT_MQ_SENDRECV 129 
#define  AUDIT_SOCKETCALL 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_log_cap (struct audit_buffer*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 struct audit_buffer* audit_log_start (struct audit_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_release_secctx (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_secid_to_secctx (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void show_special(struct audit_context *context, int *call_panic)
{
	struct audit_buffer *ab;
	int i;

	ab = audit_log_start(context, GFP_KERNEL, context->type);
	if (!ab)
		return;

	switch (context->type) {
	case AUDIT_SOCKETCALL: {
		int nargs = context->socketcall.nargs;
		audit_log_format(ab, "nargs=%d", nargs);
		for (i = 0; i < nargs; i++)
			audit_log_format(ab, " a%d=%lx", i,
				context->socketcall.args[i]);
		break; }
	case AUDIT_IPC: {
		u32 osid = context->ipc.osid;

		audit_log_format(ab, "ouid=%u ogid=%u mode=%#o",
			 context->ipc.uid, context->ipc.gid, context->ipc.mode);
		if (osid) {
			char *ctx = NULL;
			u32 len;
			if (security_secid_to_secctx(osid, &ctx, &len)) {
				audit_log_format(ab, " osid=%u", osid);
				*call_panic = 1;
			} else {
				audit_log_format(ab, " obj=%s", ctx);
				security_release_secctx(ctx, len);
			}
		}
		if (context->ipc.has_perm) {
			audit_log_end(ab);
			ab = audit_log_start(context, GFP_KERNEL,
					     AUDIT_IPC_SET_PERM);
			audit_log_format(ab,
				"qbytes=%lx ouid=%u ogid=%u mode=%#o",
				context->ipc.qbytes,
				context->ipc.perm_uid,
				context->ipc.perm_gid,
				context->ipc.perm_mode);
			if (!ab)
				return;
		}
		break; }
	case AUDIT_MQ_OPEN: {
		audit_log_format(ab,
			"oflag=0x%x mode=%#o mq_flags=0x%lx mq_maxmsg=%ld "
			"mq_msgsize=%ld mq_curmsgs=%ld",
			context->mq_open.oflag, context->mq_open.mode,
			context->mq_open.attr.mq_flags,
			context->mq_open.attr.mq_maxmsg,
			context->mq_open.attr.mq_msgsize,
			context->mq_open.attr.mq_curmsgs);
		break; }
	case AUDIT_MQ_SENDRECV: {
		audit_log_format(ab,
			"mqdes=%d msg_len=%zd msg_prio=%u "
			"abs_timeout_sec=%ld abs_timeout_nsec=%ld",
			context->mq_sendrecv.mqdes,
			context->mq_sendrecv.msg_len,
			context->mq_sendrecv.msg_prio,
			context->mq_sendrecv.abs_timeout.tv_sec,
			context->mq_sendrecv.abs_timeout.tv_nsec);
		break; }
	case AUDIT_MQ_NOTIFY: {
		audit_log_format(ab, "mqdes=%d sigev_signo=%d",
				context->mq_notify.mqdes,
				context->mq_notify.sigev_signo);
		break; }
	case AUDIT_MQ_GETSETATTR: {
		struct mq_attr *attr = &context->mq_getsetattr.mqstat;
		audit_log_format(ab,
			"mqdes=%d mq_flags=0x%lx mq_maxmsg=%ld mq_msgsize=%ld "
			"mq_curmsgs=%ld ",
			context->mq_getsetattr.mqdes,
			attr->mq_flags, attr->mq_maxmsg,
			attr->mq_msgsize, attr->mq_curmsgs);
		break; }
	case AUDIT_CAPSET: {
		audit_log_format(ab, "pid=%d", context->capset.pid);
		audit_log_cap(ab, "cap_pi", &context->capset.cap.inheritable);
		audit_log_cap(ab, "cap_pp", &context->capset.cap.permitted);
		audit_log_cap(ab, "cap_pe", &context->capset.cap.effective);
		break; }
	case AUDIT_MMAP: {
		audit_log_format(ab, "fd=%d flags=0x%x", context->mmap.fd,
				 context->mmap.flags);
		break; }
	}
	audit_log_end(ab);
}