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
struct domain {int dom_flags; scalar_t__ dom_protohdrlen; int /*<<< orphan*/  (* dom_init ) (struct domain*) ;int /*<<< orphan*/  dom_protosw; int /*<<< orphan*/  dom_mtx_s; int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 int DOM_ATTACHED ; 
 int DOM_INITIALIZED ; 
 scalar_t__ MHLEN ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int _max_linkhdr ; 
 scalar_t__ _max_protohdr ; 
 int /*<<< orphan*/  domain_proto_mtx_attr ; 
 int /*<<< orphan*/  domain_proto_mtx_grp ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max_datalen ; 
 scalar_t__ max_hdr ; 
 int max_linkhdr ; 
 scalar_t__ max_protohdr ; 
 int /*<<< orphan*/  stub1 (struct domain*) ; 

__attribute__((used)) static void
init_domain(struct domain *dp)
{
	VERIFY(dp->dom_flags & DOM_ATTACHED);

	if (!(dp->dom_flags & DOM_INITIALIZED)) {
		lck_mtx_init(&dp->dom_mtx_s, domain_proto_mtx_grp,
		    domain_proto_mtx_attr);
		dp->dom_mtx = &dp->dom_mtx_s;
		TAILQ_INIT(&dp->dom_protosw);
		if (dp->dom_init != NULL)
			dp->dom_init(dp);
		dp->dom_flags |= DOM_INITIALIZED;
	}

	/* Recompute for new protocol */
	if (_max_linkhdr < 16)		/* XXX - Sheesh; everything's ether? */
		_max_linkhdr = 16;
	_max_linkhdr = max_linkhdr;	/* round it up */

	if (dp->dom_protohdrlen > _max_protohdr)
		_max_protohdr = dp->dom_protohdrlen;
	_max_protohdr = max_protohdr;	/* round it up */

	max_hdr = max_linkhdr + max_protohdr;
	max_datalen = MHLEN - max_hdr;
}