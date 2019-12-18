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
struct ifbrhostfilter {int /*<<< orphan*/  ifbrhf_ipsrc; int /*<<< orphan*/  ifbrhf_hwsrca; int /*<<< orphan*/  ifbrhf_flags; int /*<<< orphan*/  ifbrhf_ifsname; } ;
struct bridge_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct bridge_iflist {int bif_flags; TYPE_1__ bif_hf_ipsrc; int /*<<< orphan*/  bif_hf_hwsrc; } ;

/* Variables and functions */
 int BIFF_HOST_FILTER ; 
 int ENOENT ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFBRHF_ENABLED ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bridge_iflist* bridge_lookup_member (struct bridge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ifbrhostfilter*,int) ; 

__attribute__((used)) static int
bridge_ioctl_ghostfilter(struct bridge_softc *sc, void *arg)
{
	struct ifbrhostfilter *req = arg;
	struct bridge_iflist *bif;

	bif = bridge_lookup_member(sc, req->ifbrhf_ifsname);
	if (bif == NULL)
		return (ENOENT);

	bzero(req, sizeof(struct ifbrhostfilter));
	if (bif->bif_flags & BIFF_HOST_FILTER) {
		req->ifbrhf_flags |= IFBRHF_ENABLED;
		bcopy(bif->bif_hf_hwsrc, req->ifbrhf_hwsrca,
		    ETHER_ADDR_LEN);
		req->ifbrhf_ipsrc = bif->bif_hf_ipsrc.s_addr;
	}
	return (0);
}