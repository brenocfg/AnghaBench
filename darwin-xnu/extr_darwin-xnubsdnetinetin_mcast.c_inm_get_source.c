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
struct ip_msource {int /*<<< orphan*/  ims_haddr; } ;
struct in_multi {scalar_t__ inm_nsrc; int /*<<< orphan*/  inm_srcs; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  INM_LOCK_ASSERT_HELD (struct in_multi*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct ip_msource* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip_msource*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip_msource*) ; 
 scalar_t__ in_mcast_maxgrpsrc ; 
 int /*<<< orphan*/  ip_msource_tree ; 
 struct ip_msource* ipms_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
inm_get_source(struct in_multi *inm, const in_addr_t haddr,
    const int noalloc, struct ip_msource **pims)
{
	struct ip_msource	 find;
	struct ip_msource	*ims, *nims;
#ifdef IGMP_DEBUG
	struct in_addr ia;
	char buf[MAX_IPv4_STR_LEN];
#endif
	INM_LOCK_ASSERT_HELD(inm);

	find.ims_haddr = haddr;
	ims = RB_FIND(ip_msource_tree, &inm->inm_srcs, &find);
	if (ims == NULL && !noalloc) {
		if (inm->inm_nsrc == in_mcast_maxgrpsrc)
			return (ENOSPC);
		nims = ipms_alloc(M_WAITOK);
		if (nims == NULL)
			return (ENOMEM);
		nims->ims_haddr = haddr;
		RB_INSERT(ip_msource_tree, &inm->inm_srcs, nims);
		++inm->inm_nsrc;
		ims = nims;
#ifdef IGMP_DEBUG
		ia.s_addr = htonl(haddr);
		inet_ntop(AF_INET, &ia, buf, sizeof(buf));
		IGMP_PRINTF(("%s: allocated %s as 0x%llx\n", __func__,
		    buf, (uint64_t)VM_KERNEL_ADDRPERM(ims)));
#endif
	}

	*pims = ims;
	return (0);
}