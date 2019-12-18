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
struct se_session {int /*<<< orphan*/  sess_kref; struct se_portal_group* se_tpg; } ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put_session ) (struct se_session*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct se_session*) ; 
 int /*<<< orphan*/  target_release_session ; 

void target_put_session(struct se_session *se_sess)
{
	struct se_portal_group *tpg = se_sess->se_tpg;

	if (tpg->se_tpg_tfo->put_session != NULL) {
		tpg->se_tpg_tfo->put_session(se_sess);
		return;
	}
	kref_put(&se_sess->sess_kref, target_release_session);
}