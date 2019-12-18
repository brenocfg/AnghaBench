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
struct in6_multi_mship {int /*<<< orphan*/  i6mm_maddr; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int in6_mc_join (struct ifnet*,struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct in6_multi_mship* in6_multi_mship_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_multi_mship_free (struct in6_multi_mship*) ; 

struct in6_multi_mship *
in6_joingroup(struct ifnet *ifp, struct in6_addr *mcaddr,
    int *errorp, int delay)
{
	struct in6_multi_mship *imm;
	int error;

	*errorp = 0;

	imm = in6_multi_mship_alloc(M_WAITOK);
	if (imm == NULL) {
		*errorp = ENOBUFS;
		return (NULL);
	}

	error = in6_mc_join(ifp, mcaddr, NULL, &imm->i6mm_maddr, delay);
	if (error) {
		*errorp = error;
		in6_multi_mship_free(imm);
		return (NULL);
	}

	return (imm);
}