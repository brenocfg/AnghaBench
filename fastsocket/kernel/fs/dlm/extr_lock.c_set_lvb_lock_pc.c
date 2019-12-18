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
struct dlm_rsb {int dummy; } ;
struct dlm_message {int /*<<< orphan*/  m_lvbseq; int /*<<< orphan*/  m_extra; } ;
struct dlm_lkb {int lkb_exflags; int lkb_grmode; int lkb_rqmode; int /*<<< orphan*/  lkb_lvbseq; int /*<<< orphan*/  lkb_lvbptr; } ;

/* Variables and functions */
 int DLM_LKF_VALBLK ; 
 int DLM_RESNAME_MAXLEN ; 
 int** dlm_lvb_operations ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int receive_extralen (struct dlm_message*) ; 

__attribute__((used)) static void set_lvb_lock_pc(struct dlm_rsb *r, struct dlm_lkb *lkb,
			    struct dlm_message *ms)
{
	int b;

	if (!lkb->lkb_lvbptr)
		return;

	if (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
		return;

	b = dlm_lvb_operations[lkb->lkb_grmode + 1][lkb->lkb_rqmode + 1];
	if (b == 1) {
		int len = receive_extralen(ms);
		if (len > DLM_RESNAME_MAXLEN)
			len = DLM_RESNAME_MAXLEN;
		memcpy(lkb->lkb_lvbptr, ms->m_extra, len);
		lkb->lkb_lvbseq = ms->m_lvbseq;
	}
}