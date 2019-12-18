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
typedef  int /*<<< orphan*/  wwn_t ;
struct bfa_s {int dummy; } ;
struct bfa_fcport_s {int /*<<< orphan*/  pwwn; int /*<<< orphan*/  nwwn; } ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (struct bfa_s*) ; 

wwn_t
bfa_fcport_get_wwn(struct bfa_s *bfa, bfa_boolean_t node)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);
	if (node)
		return fcport->nwwn;
	else
		return fcport->pwwn;
}