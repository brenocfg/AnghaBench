#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fc_alpabm_s {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  alpa_bm; } ;
struct bfa_fcport_s {TYPE_1__ alpabm; int /*<<< orphan*/  alpabm_valid; int /*<<< orphan*/  myalpa; } ;
struct TYPE_4__ {int /*<<< orphan*/  alpa_bm; } ;
struct bfa_fcport_loop_info_s {TYPE_2__ alpabm; int /*<<< orphan*/  alpabm_val; int /*<<< orphan*/  myalpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcport_update_loop_info(struct bfa_fcport_s *fcport,
			struct bfa_fcport_loop_info_s *loop_info)
{
	fcport->myalpa = loop_info->myalpa;
	fcport->alpabm_valid =
			loop_info->alpabm_val;
	memcpy(fcport->alpabm.alpa_bm,
			loop_info->alpabm.alpa_bm,
			sizeof(struct fc_alpabm_s));
}