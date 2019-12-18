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
struct ifbreq {int /*<<< orphan*/  ifbr_priority; int /*<<< orphan*/  ifbr_ifsname; } ;
struct bridge_softc {int dummy; } ;
struct bridge_iflist {int /*<<< orphan*/  bif_stp; } ;

/* Variables and functions */
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bridge_in_bsd_mode (struct bridge_softc*) ; 
 struct bridge_iflist* bridge_lookup_member (struct bridge_softc*,int /*<<< orphan*/ ) ; 
 int bstp_set_port_priority (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_ioctl_sifprio(struct bridge_softc *sc, void *arg)
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

	return (bstp_set_port_priority(&bif->bif_stp, req->ifbr_priority));
#else /* !BRIDGESTP */
#pragma unused(sc, arg)
	return (EOPNOTSUPP);
#endif /* !BRIDGESTP */
}