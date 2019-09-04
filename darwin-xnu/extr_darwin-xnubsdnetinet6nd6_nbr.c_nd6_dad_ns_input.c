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
struct nd_opt_nonce {int dummy; } ;
struct ifaddr {int dummy; } ;
struct dadq {int dad_lladdrlen; int /*<<< orphan*/  dad_lladdr; int /*<<< orphan*/  dad_ns_icount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAD_LOCK (struct dadq*) ; 
 int /*<<< orphan*/  DAD_REMREF (struct dadq*) ; 
 int /*<<< orphan*/  DAD_UNLOCK (struct dadq*) ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 scalar_t__ dad_enhanced ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct dadq* nd6_dad_find (struct ifaddr*,struct nd_opt_nonce*) ; 

__attribute__((used)) static void
nd6_dad_ns_input(struct ifaddr *ifa, char *lladdr,
    int lladdrlen, struct nd_opt_nonce *ndopt_nonce)
{
	struct dadq *dp;
	VERIFY(ifa != NULL);

	/* Ignore Nonce option when Enhanced DAD is disabled. */
	if (dad_enhanced == 0)
		ndopt_nonce = NULL;

	dp = nd6_dad_find(ifa, ndopt_nonce);
	if (dp == NULL)
		return;

	DAD_LOCK(dp);
	++dp->dad_ns_icount;
	if (lladdr && lladdrlen >= ETHER_ADDR_LEN) {
		memcpy(dp->dad_lladdr, lladdr, ETHER_ADDR_LEN);
		dp->dad_lladdrlen = lladdrlen;
	}
	DAD_UNLOCK(dp);
	DAD_REMREF(dp);
}