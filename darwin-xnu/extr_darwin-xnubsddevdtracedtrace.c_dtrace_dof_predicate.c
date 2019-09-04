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
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
typedef  int /*<<< orphan*/  dtrace_predicate_t ;
typedef  int /*<<< orphan*/  dtrace_difo_t ;
typedef  int /*<<< orphan*/  dof_sec_t ;
typedef  int /*<<< orphan*/  dof_hdr_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dtrace_dof_difo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dtrace_predicate_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dtrace_predicate_t *
dtrace_dof_predicate(dof_hdr_t *dof, dof_sec_t *sec, dtrace_vstate_t *vstate,
    cred_t *cr)
{
	dtrace_difo_t *dp;

	if ((dp = dtrace_dof_difo(dof, sec, vstate, cr)) == NULL)
		return (NULL);

	return (dtrace_predicate_create(dp));
}