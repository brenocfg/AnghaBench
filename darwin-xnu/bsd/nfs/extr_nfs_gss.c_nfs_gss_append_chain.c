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
struct nfsm_chain {int /*<<< orphan*/  nmc_left; scalar_t__ nmc_ptr; int /*<<< orphan*/ * nmc_mcur; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ mbuf_data (int /*<<< orphan*/ *) ; 
 scalar_t__ mbuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbuf_next (int /*<<< orphan*/ *) ; 
 int mbuf_setnext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_trailingspace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs_gss_append_chain(struct nfsm_chain *nmc, mbuf_t mc)
{
	int error = 0;
	mbuf_t mb, tail;

	/* Connect the mbuf chains */
	error = mbuf_setnext(nmc->nmc_mcur, mc);
	if (error)
		return (error);

	/* Find the last mbuf in the chain */
	tail = NULL;
	for (mb = mc; mb; mb = mbuf_next(mb))
		tail = mb;

	nmc->nmc_mcur = tail;
	nmc->nmc_ptr = (caddr_t) mbuf_data(tail) + mbuf_len(tail);
	nmc->nmc_left = mbuf_trailingspace(tail);

	return (0);
}