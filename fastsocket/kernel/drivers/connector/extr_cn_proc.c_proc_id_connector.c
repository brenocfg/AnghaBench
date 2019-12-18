#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct task_struct {int /*<<< orphan*/  tgid; int /*<<< orphan*/  pid; } ;
struct TYPE_6__ {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;
struct TYPE_5__ {int /*<<< orphan*/  rgid; int /*<<< orphan*/  ruid; } ;
struct TYPE_7__ {TYPE_2__ e; TYPE_1__ r; int /*<<< orphan*/  process_tgid; int /*<<< orphan*/  process_pid; } ;
struct TYPE_8__ {TYPE_3__ id; } ;
struct proc_event {int what; int /*<<< orphan*/  timestamp_ns; int /*<<< orphan*/  cpu; TYPE_4__ event_data; } ;
struct cred {int /*<<< orphan*/  egid; int /*<<< orphan*/  gid; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;
struct cn_msg {int len; scalar_t__ ack; int /*<<< orphan*/  id; int /*<<< orphan*/  seq; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CN_IDX_PROC ; 
 int CN_PROC_MSG_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PROC_EVENT_GID ; 
 int PROC_EVENT_UID ; 
 struct cred* __task_cred (struct task_struct*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cn_netlink_send (struct cn_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cn_proc_event_id ; 
 int /*<<< orphan*/  get_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_ts (struct timespec*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proc_event_num_listeners ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  timespec_to_ns (struct timespec*) ; 

void proc_id_connector(struct task_struct *task, int which_id)
{
	struct cn_msg *msg;
	struct proc_event *ev;
	__u8 buffer[CN_PROC_MSG_SIZE];
	struct timespec ts;
	const struct cred *cred;

	if (atomic_read(&proc_event_num_listeners) < 1)
		return;

	msg = (struct cn_msg*)buffer;
	ev = (struct proc_event*)msg->data;
	ev->what = which_id;
	ev->event_data.id.process_pid = task->pid;
	ev->event_data.id.process_tgid = task->tgid;
	rcu_read_lock();
	cred = __task_cred(task);
	if (which_id == PROC_EVENT_UID) {
		ev->event_data.id.r.ruid = cred->uid;
		ev->event_data.id.e.euid = cred->euid;
	} else if (which_id == PROC_EVENT_GID) {
		ev->event_data.id.r.rgid = cred->gid;
		ev->event_data.id.e.egid = cred->egid;
	} else {
		rcu_read_unlock();
	     	return;
	}
	rcu_read_unlock();
	get_seq(&msg->seq, &ev->cpu);
	ktime_get_ts(&ts); /* get high res monotonic timestamp */
	put_unaligned(timespec_to_ns(&ts), (__u64 *)&ev->timestamp_ns);

	memcpy(&msg->id, &cn_proc_event_id, sizeof(msg->id));
	msg->ack = 0; /* not used */
	msg->len = sizeof(*ev);
	cn_netlink_send(msg, CN_IDX_PROC, GFP_KERNEL);
}