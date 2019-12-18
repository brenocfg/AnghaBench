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
struct in_msource {int /*<<< orphan*/ * imsl_st; } ;
struct in_mfilter {int /*<<< orphan*/  imf_sources; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MCAST_UNDEFINED ; 
 struct ip_msource* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip_msource*) ; 
 int /*<<< orphan*/  ip_msource_tree ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imf_prune(struct in_mfilter *imf, const struct sockaddr_in *psin)
{
	struct ip_msource	 find;
	struct ip_msource	*ims;
	struct in_msource	*lims;

	/* key is host byte order */
	find.ims_haddr = ntohl(psin->sin_addr.s_addr);
	ims = RB_FIND(ip_msource_tree, &imf->imf_sources, &find);
	if (ims == NULL)
		return (ENOENT);
	lims = (struct in_msource *)ims;
	lims->imsl_st[1] = MCAST_UNDEFINED;
	return (0);
}