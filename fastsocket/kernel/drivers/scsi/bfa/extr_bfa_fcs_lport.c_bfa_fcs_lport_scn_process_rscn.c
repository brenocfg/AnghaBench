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
typedef  int u32 ;
struct fchs_s {int dummy; } ;
struct fc_rscn_pl_s {TYPE_2__* event; int /*<<< orphan*/  payldlen; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_portid_rscn; int /*<<< orphan*/  num_rscn; } ;
struct bfa_fcs_lport_s {TYPE_1__ stats; int /*<<< orphan*/  fcs; } ;
typedef  scalar_t__ bfa_boolean_t ;
struct TYPE_4__ {int portid; int format; int /*<<< orphan*/  qualifier; } ;

/* Variables and functions */
 scalar_t__ BFA_FALSE ; 
 scalar_t__ BFA_TRUE ; 
 int /*<<< orphan*/  FC_FABRIC_NAME_RSCN_EVENT ; 
 int /*<<< orphan*/  FC_QOS_RSCN_EVENT ; 
#define  FC_RSCN_FORMAT_AREA 131 
#define  FC_RSCN_FORMAT_DOMAIN 130 
#define  FC_RSCN_FORMAT_FABRIC 129 
#define  FC_RSCN_FORMAT_PORTID 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ms_fabric_rscn (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_query (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_scn_multiport_rscn (struct bfa_fcs_lport_s*,int,int) ; 
 int /*<<< orphan*/  bfa_fcs_lport_scn_portid_rscn (struct bfa_fcs_lport_s*,int) ; 
 int /*<<< orphan*/  bfa_fcs_lport_scn_send_ls_acc (struct bfa_fcs_lport_s*,struct fchs_s*) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

void
bfa_fcs_lport_scn_process_rscn(struct bfa_fcs_lport_s *port,
			struct fchs_s *fchs, u32 len)
{
	struct fc_rscn_pl_s *rscn = (struct fc_rscn_pl_s *) (fchs + 1);
	int             num_entries;
	u32        rscn_pid;
	bfa_boolean_t   nsquery = BFA_FALSE, found;
	int             i = 0, j;

	num_entries =
		(be16_to_cpu(rscn->payldlen) -
		 sizeof(u32)) / sizeof(rscn->event[0]);

	bfa_trc(port->fcs, num_entries);

	port->stats.num_rscn++;

	bfa_fcs_lport_scn_send_ls_acc(port, fchs);

	for (i = 0; i < num_entries; i++) {
		rscn_pid = rscn->event[i].portid;

		bfa_trc(port->fcs, rscn->event[i].format);
		bfa_trc(port->fcs, rscn_pid);

		/* check for duplicate entries in the list */
		found = BFA_FALSE;
		for (j = 0; j < i; j++) {
			if (rscn->event[j].portid == rscn_pid) {
				found = BFA_TRUE;
				break;
			}
		}

		/* if found in down the list, pid has been already processed */
		if (found) {
			bfa_trc(port->fcs, rscn_pid);
			continue;
		}

		switch (rscn->event[i].format) {
		case FC_RSCN_FORMAT_PORTID:
			if (rscn->event[i].qualifier == FC_QOS_RSCN_EVENT) {
				/*
				 * Ignore this event.
				 * f/w would have processed it
				 */
				bfa_trc(port->fcs, rscn_pid);
			} else {
				port->stats.num_portid_rscn++;
				bfa_fcs_lport_scn_portid_rscn(port, rscn_pid);
			}
		break;

		case FC_RSCN_FORMAT_FABRIC:
			if (rscn->event[i].qualifier ==
					FC_FABRIC_NAME_RSCN_EVENT) {
				bfa_fcs_lport_ms_fabric_rscn(port);
				break;
			}
			/* !!!!!!!!! Fall Through !!!!!!!!!!!!! */

		case FC_RSCN_FORMAT_AREA:
		case FC_RSCN_FORMAT_DOMAIN:
			nsquery = BFA_TRUE;
			bfa_fcs_lport_scn_multiport_rscn(port,
							rscn->event[i].format,
							rscn_pid);
			break;


		default:
			WARN_ON(1);
			nsquery = BFA_TRUE;
		}
	}

	/*
	 * If any of area, domain or fabric RSCN is received, do a fresh
	 * discovery to find new devices.
	 */
	if (nsquery)
		bfa_fcs_lport_ns_query(port);
}