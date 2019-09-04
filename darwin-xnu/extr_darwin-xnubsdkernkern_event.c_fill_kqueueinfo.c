#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vinfo_stat {int vst_blksize; int /*<<< orphan*/  vst_ino; int /*<<< orphan*/  vst_mode; int /*<<< orphan*/  vst_size; } ;
struct kqworkloop {int /*<<< orphan*/  kqwl_dynamicid; } ;
struct kqueue_info {int kq_state; struct vinfo_stat kq_stat; } ;
struct kqueue {int kq_state; int /*<<< orphan*/  kq_count; } ;
struct kevent_qos_s {int dummy; } ;
struct kevent64_s {int dummy; } ;
struct kevent {int dummy; } ;

/* Variables and functions */
 int KQ_DYNAMIC ; 
 int KQ_KEV32 ; 
 int KQ_KEV64 ; 
 int KQ_KEV_QOS ; 
 int KQ_SEL ; 
 int KQ_SLEEP ; 
 int KQ_WORKLOOP ; 
 int KQ_WORKQ ; 
 int /*<<< orphan*/  S_IFIFO ; 

int
fill_kqueueinfo(struct kqueue *kq, struct kqueue_info * kinfo)
{
	struct vinfo_stat * st;

	st = &kinfo->kq_stat;

	st->vst_size = kq->kq_count;
	if (kq->kq_state & KQ_KEV_QOS)
		st->vst_blksize = sizeof(struct kevent_qos_s);
	else if (kq->kq_state & KQ_KEV64)
		st->vst_blksize = sizeof(struct kevent64_s);
	else
		st->vst_blksize = sizeof(struct kevent);
	st->vst_mode = S_IFIFO;
	st->vst_ino = (kq->kq_state & KQ_DYNAMIC) ?
		((struct kqworkloop *)kq)->kqwl_dynamicid : 0;

	/* flags exported to libproc as PROC_KQUEUE_* (sys/proc_info.h) */
#define PROC_KQUEUE_MASK (KQ_SEL|KQ_SLEEP|KQ_KEV32|KQ_KEV64|KQ_KEV_QOS|KQ_WORKQ|KQ_WORKLOOP)
	kinfo->kq_state = kq->kq_state & PROC_KQUEUE_MASK;

	return (0);
}