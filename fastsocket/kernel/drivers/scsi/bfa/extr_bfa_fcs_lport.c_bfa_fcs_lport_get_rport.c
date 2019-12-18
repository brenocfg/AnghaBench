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
typedef  scalar_t__ wwn_t ;
typedef  int u32 ;
struct list_head {int dummy; } ;
struct bfa_fcs_s {int dummy; } ;
struct bfa_fcs_rport_s {int pid; scalar_t__ pwwn; } ;
struct bfa_fcs_lport_s {struct list_head rport_q; struct bfa_fcs_s* fcs; } ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 int bfa_ntoh3b (int) ; 
 struct list_head* bfa_q_first (struct list_head*) ; 
 struct list_head* bfa_q_next (struct list_head*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fcs_s*,int) ; 
 int /*<<< orphan*/  memcmp (scalar_t__*,scalar_t__*,int) ; 

wwn_t
bfa_fcs_lport_get_rport(struct bfa_fcs_lport_s *port, wwn_t wwn, int index,
		int nrports, bfa_boolean_t bwwn)
{
	struct list_head	*qh, *qe;
	struct bfa_fcs_rport_s *rport = NULL;
	int	i;
	struct bfa_fcs_s	*fcs;

	if (port == NULL || nrports == 0)
		return (wwn_t) 0;

	fcs = port->fcs;
	bfa_trc(fcs, (u32) nrports);

	i = 0;
	qh = &port->rport_q;
	qe = bfa_q_first(qh);

	while ((qe != qh) && (i < nrports)) {
		rport = (struct bfa_fcs_rport_s *) qe;
		if (bfa_ntoh3b(rport->pid) > 0xFFF000) {
			qe = bfa_q_next(qe);
			bfa_trc(fcs, (u32) rport->pwwn);
			bfa_trc(fcs, rport->pid);
			bfa_trc(fcs, i);
			continue;
		}

		if (bwwn) {
			if (!memcmp(&wwn, &rport->pwwn, 8))
				break;
		} else {
			if (i == index)
				break;
		}

		i++;
		qe = bfa_q_next(qe);
	}

	bfa_trc(fcs, i);
	if (rport)
		return rport->pwwn;
	else
		return (wwn_t) 0;
}