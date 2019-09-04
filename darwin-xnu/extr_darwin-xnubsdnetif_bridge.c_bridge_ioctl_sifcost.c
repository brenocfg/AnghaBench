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
struct bridge_softc {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int
bridge_ioctl_sifcost(struct bridge_softc *sc, void *arg)
{
#if BRIDGESTP
	struct ifbreq *req = arg;
	struct bridge_iflist *bif;

	if (!bridge_in_bsd_mode(sc)) {
		return (EOPNOTSUPP);
	}
	bif = bridge_lookup_member(sc, req->ifbr_ifsname);
	if (bif == NULL)
		return (ENOENT);

	return (bstp_set_path_cost(&bif->bif_stp, req->ifbr_path_cost));
#else /* !BRIDGESTP */
#pragma unused(sc, arg)
	return (EOPNOTSUPP);
#endif /* !BRIDGESTP */
}