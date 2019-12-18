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
struct common_audit_data {int /*<<< orphan*/  (* lsm_post_audit ) (struct audit_buffer*,struct common_audit_data*) ;int /*<<< orphan*/  (* lsm_pre_audit ) (struct audit_buffer*,struct common_audit_data*) ;} ;
struct audit_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  audit_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_AVC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dump_common_audit_data (struct audit_buffer*,struct common_audit_data*) ; 
 int /*<<< orphan*/  stub1 (struct audit_buffer*,struct common_audit_data*) ; 
 int /*<<< orphan*/  stub2 (struct audit_buffer*,struct common_audit_data*) ; 

void common_lsm_audit(struct common_audit_data *a)
{
	struct audit_buffer *ab;

	if (a == NULL)
		return;
	/* we use GFP_ATOMIC so we won't sleep */
	ab = audit_log_start(current->audit_context, GFP_ATOMIC, AUDIT_AVC);

	if (ab == NULL)
		return;

	if (a->lsm_pre_audit)
		a->lsm_pre_audit(ab, a);

	dump_common_audit_data(ab, a);

	if (a->lsm_post_audit)
		a->lsm_post_audit(ab, a);

	audit_log_end(ab);
}