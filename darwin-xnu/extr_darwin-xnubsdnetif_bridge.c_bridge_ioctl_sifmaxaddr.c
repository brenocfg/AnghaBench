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
struct ifbreq {int /*<<< orphan*/  ifbr_addrmax; int /*<<< orphan*/  ifbr_ifsname; } ;
struct bridge_softc {int dummy; } ;
struct bridge_iflist {int /*<<< orphan*/  bif_addrmax; } ;

/* Variables and functions */
 int ENOENT ; 
 struct bridge_iflist* bridge_lookup_member (struct bridge_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_ioctl_sifmaxaddr(struct bridge_softc *sc, void *arg)
{
	struct ifbreq *req = arg;
	struct bridge_iflist *bif;

	bif = bridge_lookup_member(sc, req->ifbr_ifsname);
	if (bif == NULL)
		return (ENOENT);

	bif->bif_addrmax = req->ifbr_addrmax;
	return (0);
}