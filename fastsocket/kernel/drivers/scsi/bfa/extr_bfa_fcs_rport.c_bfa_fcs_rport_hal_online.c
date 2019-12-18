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
struct bfa_rport_info_s {int /*<<< orphan*/  max_frmsz; int /*<<< orphan*/  cisc; int /*<<< orphan*/  fc_class; int /*<<< orphan*/  vf_en; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  lp_tag; int /*<<< orphan*/  local_pid; int /*<<< orphan*/  pid; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  bfa_rport; int /*<<< orphan*/  maxfrsize; int /*<<< orphan*/  cisc; int /*<<< orphan*/  fc_cos; int /*<<< orphan*/  pid; struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_lport_s {TYPE_1__* fabric; int /*<<< orphan*/  lp_tag; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_vf; int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_rport_online (int /*<<< orphan*/ ,struct bfa_rport_info_s*) ; 

__attribute__((used)) static void
bfa_fcs_rport_hal_online(struct bfa_fcs_rport_s *rport)
{
	struct bfa_fcs_lport_s *port = rport->port;
	struct bfa_rport_info_s rport_info;

	rport_info.pid = rport->pid;
	rport_info.local_pid = port->pid;
	rport_info.lp_tag = port->lp_tag;
	rport_info.vf_id = port->fabric->vf_id;
	rport_info.vf_en = port->fabric->is_vf;
	rport_info.fc_class = rport->fc_cos;
	rport_info.cisc = rport->cisc;
	rport_info.max_frmsz = rport->maxfrsize;
	bfa_rport_online(rport->bfa_rport, &rport_info);
}