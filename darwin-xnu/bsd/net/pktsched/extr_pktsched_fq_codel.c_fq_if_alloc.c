#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int /*<<< orphan*/  if_snd; } ;
struct TYPE_5__ {int /*<<< orphan*/  fqs_fclist; int /*<<< orphan*/  fqs_pkt_droplimit; int /*<<< orphan*/  fqs_update_interval; int /*<<< orphan*/  fqs_target_qdelay; int /*<<< orphan*/  fqs_ptype; int /*<<< orphan*/ * fqs_ifq; } ;
typedef  TYPE_1__ fq_if_t ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_PKT_DROP_LIMIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_if_size ; 
 int /*<<< orphan*/  fq_if_zone ; 
 int /*<<< orphan*/  ifclassq_calc_target_qdelay (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifclassq_calc_update_interval (int /*<<< orphan*/ *) ; 
 TYPE_1__* zalloc (int /*<<< orphan*/ ) ; 

fq_if_t *
fq_if_alloc(struct ifnet *ifp, classq_pkt_type_t ptype)
{
	fq_if_t *fqs;
	fqs = zalloc(fq_if_zone);
	if (fqs == NULL)
		return (NULL);

	bzero(fqs, fq_if_size);
	fqs->fqs_ifq = &ifp->if_snd;
	fqs->fqs_ptype = ptype;

	/* Calculate target queue delay */
	ifclassq_calc_target_qdelay(ifp, &fqs->fqs_target_qdelay);

	/* Calculate update interval */
	ifclassq_calc_update_interval(&fqs->fqs_update_interval);

	/* Configure packet drop limit across all queues */
	fqs->fqs_pkt_droplimit = IFCQ_PKT_DROP_LIMIT(&ifp->if_snd);
	STAILQ_INIT(&fqs->fqs_fclist);
	return (fqs);
}