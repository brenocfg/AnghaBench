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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct ip_msource {int dummy; } ;
struct in_msource {int /*<<< orphan*/ * imsl_st; int /*<<< orphan*/  ims_haddr; } ;
struct in_mfilter {int /*<<< orphan*/  imf_nsrc; int /*<<< orphan*/  imf_sources; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCAST_UNDEFINED ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip_msource*) ; 
 struct in_msource* inms_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_msource_tree ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct in_msource *
imf_graft(struct in_mfilter *imf, const uint8_t st1,
    const struct sockaddr_in *psin)
{
	struct in_msource	*lims;

	lims = inms_alloc(M_WAITOK);
	if (lims == NULL)
		return (NULL);
	lims->ims_haddr = ntohl(psin->sin_addr.s_addr);
	lims->imsl_st[0] = MCAST_UNDEFINED;
	lims->imsl_st[1] = st1;
	RB_INSERT(ip_msource_tree, &imf->imf_sources,
	    (struct ip_msource *)lims);
	++imf->imf_nsrc;

	return (lims);
}