#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfa_fcport_s {int /*<<< orphan*/  nwwn; TYPE_3__* bfa; int /*<<< orphan*/  pwwn; } ;
struct TYPE_5__ {TYPE_1__* attr; } ;
struct TYPE_6__ {TYPE_2__ ioc; } ;
struct TYPE_4__ {int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_trc (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcport_set_wwns(struct bfa_fcport_s *fcport)
{
	fcport->pwwn = fcport->bfa->ioc.attr->pwwn;
	fcport->nwwn = fcport->bfa->ioc.attr->nwwn;

	bfa_trc(fcport->bfa, fcport->pwwn);
	bfa_trc(fcport->bfa, fcport->nwwn);
}