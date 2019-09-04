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
struct nfsm_chain {int nmc_flags; int /*<<< orphan*/  nmc_left; scalar_t__ nmc_ptr; int /*<<< orphan*/ * nmc_mcur; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int NFSM_CHAIN_FLAG_ADD_CLUSTERS ; 
 scalar_t__ mbuf_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_setlen (int /*<<< orphan*/ *,scalar_t__) ; 
 int mbuf_setnext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_trailingspace (int /*<<< orphan*/ *) ; 
 size_t nfs_mbuf_minclsize ; 
 int /*<<< orphan*/  nfsm_mbuf_get (int,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
nfsm_chain_new_mbuf(struct nfsm_chain *nmc, size_t sizehint)
{
	mbuf_t mb;
	int error = 0;

	if (nmc->nmc_flags & NFSM_CHAIN_FLAG_ADD_CLUSTERS)
		sizehint = nfs_mbuf_minclsize;

	/* allocate a new mbuf */
	nfsm_mbuf_get(error, &mb, sizehint);
	if (error)
		return (error);
	if (mb == NULL)
		panic("got NULL mbuf?");

	/* do we have a current mbuf? */
	if (nmc->nmc_mcur) {
		/* first cap off current mbuf */
		mbuf_setlen(nmc->nmc_mcur, nmc->nmc_ptr - (caddr_t)mbuf_data(nmc->nmc_mcur));
		/* then append the new mbuf */
		error = mbuf_setnext(nmc->nmc_mcur, mb);
		if (error) {
			mbuf_free(mb);
			return (error);
		}
	}

	/* set up for using the new mbuf */
	nmc->nmc_mcur = mb;
	nmc->nmc_ptr = mbuf_data(mb);
	nmc->nmc_left = mbuf_trailingspace(mb);

	return (0);
}