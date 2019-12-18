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
struct protosw {int pr_flags; } ;
struct domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int PR_ATTACHED ; 
 int PR_INITIALIZED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  encaptab ; 

__attribute__((used)) static void
encap_init(struct protosw *pp, struct domain *dp)
{
#pragma unused(dp)
	static int encap_initialized = 0;

	VERIFY((pp->pr_flags & (PR_INITIALIZED|PR_ATTACHED)) == PR_ATTACHED);

	/* This gets called by more than one protocols, so initialize once */
	if (encap_initialized)
		return;
	encap_initialized = 1;
#if 0
	/*
	 * we cannot use LIST_INIT() here, since drivers may want to call
	 * encap_attach(), on driver attach.  encap_init() will be called
	 * on AF_INET{,6} initialization, which happens after driver
	 * initialization - using LIST_INIT() here can nuke encap_attach()
	 * from drivers.
	 */
	LIST_INIT(&encaptab);
#endif
}