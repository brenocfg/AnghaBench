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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct ip_msource {int /*<<< orphan*/  ims_haddr; } ;
struct in_msource {int /*<<< orphan*/ * imsl_st; int /*<<< orphan*/  ims_haddr; } ;
struct in_mfilter {scalar_t__ imf_nsrc; int /*<<< orphan*/  imf_sources; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  MCAST_UNDEFINED ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct ip_msource* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip_msource*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip_msource*) ; 
 scalar_t__ in_mcast_maxsocksrc ; 
 struct in_msource* inms_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_msource_tree ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imf_get_source(struct in_mfilter *imf, const struct sockaddr_in *psin,
    struct in_msource **plims)
{
	struct ip_msource	 find;
	struct ip_msource	*ims;
	struct in_msource	*lims;
	int			 error;

	error = 0;
	ims = NULL;
	lims = NULL;

	/* key is host byte order */
	find.ims_haddr = ntohl(psin->sin_addr.s_addr);
	ims = RB_FIND(ip_msource_tree, &imf->imf_sources, &find);
	lims = (struct in_msource *)ims;
	if (lims == NULL) {
		if (imf->imf_nsrc == in_mcast_maxsocksrc)
			return (ENOSPC);
		lims = inms_alloc(M_WAITOK);
		if (lims == NULL)
			return (ENOMEM);
		lims->ims_haddr = find.ims_haddr;
		lims->imsl_st[0] = MCAST_UNDEFINED;
		RB_INSERT(ip_msource_tree, &imf->imf_sources,
		    (struct ip_msource *)lims);
		++imf->imf_nsrc;
	}

	*plims = lims;

	return (error);
}