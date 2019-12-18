#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lockd_ans {int la_flags; scalar_t__ la_pid; scalar_t__ la_start; scalar_t__ la_len; scalar_t__ la_fh_len; int /*<<< orphan*/  la_fh; } ;
struct TYPE_5__ {scalar_t__ l_pid; scalar_t__ l_start; scalar_t__ l_len; } ;
struct TYPE_6__ {scalar_t__ lm_fh_len; int /*<<< orphan*/  lm_fh; TYPE_1__ lm_fl; } ;
struct TYPE_7__ {TYPE_2__ lmr_msg; } ;
typedef  TYPE_3__ LOCKD_MSG_REQUEST ;

/* Variables and functions */
 int LOCKD_ANS_LOCK_INFO ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
nfs_lockdmsg_compare_to_answer(LOCKD_MSG_REQUEST *msgreq, struct lockd_ans *ansp)
{
	if (!(ansp->la_flags & LOCKD_ANS_LOCK_INFO))
		return 1;
	if (msgreq->lmr_msg.lm_fl.l_pid != ansp->la_pid)
		return 1;
	if (msgreq->lmr_msg.lm_fl.l_start != ansp->la_start)
		return 1;
	if (msgreq->lmr_msg.lm_fl.l_len != ansp->la_len)
		return 1;
	if (msgreq->lmr_msg.lm_fh_len != ansp->la_fh_len)
		return 1;
	if (bcmp(msgreq->lmr_msg.lm_fh, ansp->la_fh, ansp->la_fh_len))
		return 1;
	return 0;
}