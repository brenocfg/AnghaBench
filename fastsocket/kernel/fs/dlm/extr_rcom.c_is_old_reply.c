#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  h_nodeid; } ;
struct dlm_rcom {int rc_type; scalar_t__ rc_seq_reply; TYPE_1__ rc_header; } ;
struct dlm_ls {int /*<<< orphan*/  ls_recover_lock; scalar_t__ ls_recover_seq; } ;

/* Variables and functions */
#define  DLM_RCOM_LOCK_REPLY 131 
#define  DLM_RCOM_LOOKUP_REPLY 130 
#define  DLM_RCOM_NAMES_REPLY 129 
#define  DLM_RCOM_STATUS_REPLY 128 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_old_reply(struct dlm_ls *ls, struct dlm_rcom *rc)
{
	uint64_t seq;
	int rv = 0;

	switch (rc->rc_type) {
	case DLM_RCOM_STATUS_REPLY:
	case DLM_RCOM_NAMES_REPLY:
	case DLM_RCOM_LOOKUP_REPLY:
	case DLM_RCOM_LOCK_REPLY:
		spin_lock(&ls->ls_recover_lock);
		seq = ls->ls_recover_seq;
		spin_unlock(&ls->ls_recover_lock);
		if (rc->rc_seq_reply != seq) {
			log_debug(ls, "ignoring old reply %x from %d "
				      "seq_reply %llx expect %llx",
				      rc->rc_type, rc->rc_header.h_nodeid,
				      (unsigned long long)rc->rc_seq_reply,
				      (unsigned long long)seq);
			rv = 1;
		}
	}
	return rv;
}