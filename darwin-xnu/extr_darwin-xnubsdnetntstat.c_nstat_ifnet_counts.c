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
struct nstat_ifnet_cookie {struct ifnet* ifp; } ;
struct nstat_counts {scalar_t__ nstat_cell_txbytes; scalar_t__ nstat_cell_rxbytes; int /*<<< orphan*/  nstat_txbytes; int /*<<< orphan*/  nstat_txpackets; int /*<<< orphan*/  nstat_rxbytes; int /*<<< orphan*/  nstat_rxpackets; } ;
struct ifnet {int /*<<< orphan*/  if_obytes; int /*<<< orphan*/  if_opackets; int /*<<< orphan*/  if_ibytes; int /*<<< orphan*/  if_ipackets; } ;
typedef  scalar_t__ nstat_provider_cookie_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  bzero (struct nstat_counts*,int) ; 
 scalar_t__ nstat_ifnet_gone (scalar_t__) ; 

__attribute__((used)) static errno_t
nstat_ifnet_counts(
	nstat_provider_cookie_t	cookie,
	struct nstat_counts	*out_counts,
	int			*out_gone)
{
	struct nstat_ifnet_cookie *ifcookie =
	    (struct nstat_ifnet_cookie *)cookie;
	struct ifnet *ifp = ifcookie->ifp;

	if (out_gone) *out_gone = 0;

	// if the ifnet is gone, we should stop using it
	if (nstat_ifnet_gone(cookie))
	{
		if (out_gone) *out_gone = 1;
		return EINVAL;
	}

	bzero(out_counts, sizeof(*out_counts));
	out_counts->nstat_rxpackets = ifp->if_ipackets;
	out_counts->nstat_rxbytes = ifp->if_ibytes;
	out_counts->nstat_txpackets = ifp->if_opackets;
	out_counts->nstat_txbytes = ifp->if_obytes;
	out_counts->nstat_cell_rxbytes = out_counts->nstat_cell_txbytes = 0;
	return 0;
}