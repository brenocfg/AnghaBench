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
struct TYPE_2__ {int /*<<< orphan*/  fdisc_sent; } ;
struct bfa_fcs_vport_s {TYPE_1__ vport_stats; int /*<<< orphan*/  lps; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vport_bfa (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  __vport_nwwn (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  __vport_pwwn (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  bfa_fcport_get_maxfrsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_lps_fdisc (int /*<<< orphan*/ ,struct bfa_fcs_vport_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_vport_do_fdisc(struct bfa_fcs_vport_s *vport)
{
	bfa_lps_fdisc(vport->lps, vport,
		bfa_fcport_get_maxfrsize(__vport_bfa(vport)),
		__vport_pwwn(vport), __vport_nwwn(vport));
	vport->vport_stats.fdisc_sent++;
}