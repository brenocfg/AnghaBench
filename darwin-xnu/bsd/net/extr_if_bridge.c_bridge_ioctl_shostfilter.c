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
struct ifbrhostfilter {int ifbrhf_flags; scalar_t__ ifbrhf_ipsrc; int /*<<< orphan*/  ifbrhf_hwsrca; int /*<<< orphan*/  ifbrhf_ifsname; } ;
struct bridge_softc {int dummy; } ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct bridge_iflist {int bif_flags; TYPE_1__ bif_hf_ipsrc; int /*<<< orphan*/  bif_hf_hwsrc; } ;
struct TYPE_4__ {int /*<<< orphan*/  nas_vmnet_total; } ;

/* Variables and functions */
 int BIFF_HF_HWSRC ; 
 int BIFF_HF_IPSRC ; 
 int BIFF_HOST_FILTER ; 
 int ENOENT ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFBRHF_ENABLED ; 
 int IFBRHF_HWSRC ; 
 int IFBRHF_IPSRC ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  INC_ATOMIC_INT64_LIM (int /*<<< orphan*/ ) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bridge_iflist* bridge_lookup_member (struct bridge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethernulladdr ; 
 TYPE_2__ net_api_stats ; 

__attribute__((used)) static int
bridge_ioctl_shostfilter(struct bridge_softc *sc, void *arg)
{
	struct ifbrhostfilter *req = arg;
	struct bridge_iflist *bif;

	bif = bridge_lookup_member(sc, req->ifbrhf_ifsname);
	if (bif == NULL)
		return (ENOENT);

	INC_ATOMIC_INT64_LIM(net_api_stats.nas_vmnet_total);

	if (req->ifbrhf_flags & IFBRHF_ENABLED) {
		bif->bif_flags |= BIFF_HOST_FILTER;

		if (req->ifbrhf_flags & IFBRHF_HWSRC) {
			bcopy(req->ifbrhf_hwsrca, bif->bif_hf_hwsrc,
			    ETHER_ADDR_LEN);
			if (bcmp(req->ifbrhf_hwsrca, ethernulladdr,
			    ETHER_ADDR_LEN) != 0)
				bif->bif_flags |= BIFF_HF_HWSRC;
			else
				bif->bif_flags &= ~BIFF_HF_HWSRC;
		}
		if (req->ifbrhf_flags & IFBRHF_IPSRC) {
			bif->bif_hf_ipsrc.s_addr = req->ifbrhf_ipsrc;
			if (bif->bif_hf_ipsrc.s_addr != INADDR_ANY)
				bif->bif_flags |= BIFF_HF_IPSRC;
			else
				bif->bif_flags &= ~BIFF_HF_IPSRC;
		}
	} else {
		bif->bif_flags &= ~(BIFF_HOST_FILTER | BIFF_HF_HWSRC |
		    BIFF_HF_IPSRC);
		bzero(bif->bif_hf_hwsrc, ETHER_ADDR_LEN);
		bif->bif_hf_ipsrc.s_addr = INADDR_ANY;
	}

	return (0);
}