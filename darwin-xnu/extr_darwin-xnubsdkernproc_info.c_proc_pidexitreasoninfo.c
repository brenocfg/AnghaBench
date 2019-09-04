#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct proc_exitreasoninfo {scalar_t__ eri_reason_buf_size; int /*<<< orphan*/  eri_kcd_buf; int /*<<< orphan*/  eri_flags; int /*<<< orphan*/  eri_code; int /*<<< orphan*/  eri_namespace; } ;
struct proc_exitreasonbasicinfo {scalar_t__ beri_reason_buf_size; int /*<<< orphan*/  beri_flags; int /*<<< orphan*/  beri_code; int /*<<< orphan*/  beri_namespace; } ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ pid_t ;
struct TYPE_7__ {int /*<<< orphan*/  osr_flags; int /*<<< orphan*/  osr_code; int /*<<< orphan*/  osr_namespace; int /*<<< orphan*/ * osr_kcd_buf; int /*<<< orphan*/  osr_kcd_descriptor; } ;
struct TYPE_6__ {scalar_t__ p_ppid; int p_lflag; scalar_t__ p_oppid; TYPE_5__* p_exit_reason; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 int ENOMEM ; 
 TYPE_5__* OS_REASON_NULL ; 
 int P_LTRACED ; 
 int /*<<< orphan*/  assert (int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kcdata_memory_get_used_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 scalar_t__ proc_selfpid () ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 

int
proc_pidexitreasoninfo(proc_t p, struct proc_exitreasoninfo *peri, struct proc_exitreasonbasicinfo *pberi)
{
	uint32_t reason_data_size = 0;
	int error = 0;
	pid_t selfpid = proc_selfpid();

	proc_lock(p);

	/*
	 * One (and only one) of peri and pberi must be non-NULL.
	 */
	assert((peri != NULL) || (pberi != NULL));
	assert((peri == NULL) || (pberi == NULL));

	/*
	 * Allow access to the parent of the exiting
	 * child or the parent debugger only.
	 */
	do {
		if (p->p_ppid == selfpid)
			break;  /* parent => ok */

		if ((p->p_lflag & P_LTRACED) != 0 &&
		    (p->p_oppid == selfpid))
			break;  /* parent-in-waiting => ok */

		proc_unlock(p);
		return EACCES;
	} while (0);

	if (p->p_exit_reason == OS_REASON_NULL) {
		proc_unlock(p);
		return ENOENT;
	}

	if (p->p_exit_reason->osr_kcd_buf != NULL) {
		reason_data_size = kcdata_memory_get_used_bytes(&p->p_exit_reason->osr_kcd_descriptor);
	}

	if (peri != NULL) {
		peri->eri_namespace = p->p_exit_reason->osr_namespace;
		peri->eri_code = p->p_exit_reason->osr_code;
		peri->eri_flags = p->p_exit_reason->osr_flags;

		if ((peri->eri_kcd_buf == 0) || (peri->eri_reason_buf_size < reason_data_size)) {
			proc_unlock(p);
			return ENOMEM;
		}

		peri->eri_reason_buf_size = reason_data_size;
		if (reason_data_size != 0) {
			error = copyout(p->p_exit_reason->osr_kcd_buf, peri->eri_kcd_buf, reason_data_size);
		}
	} else {
		pberi->beri_namespace =  p->p_exit_reason->osr_namespace;
		pberi->beri_code = p->p_exit_reason->osr_code;
		pberi->beri_flags = p->p_exit_reason->osr_flags;
		pberi->beri_reason_buf_size = reason_data_size;
	}

	proc_unlock(p);

	return error;
}