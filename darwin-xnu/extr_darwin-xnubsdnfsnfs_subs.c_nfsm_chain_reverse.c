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
typedef  scalar_t__ uint32_t ;
struct nfsm_chain {scalar_t__ nmc_ptr; int /*<<< orphan*/  nmc_mhead; int /*<<< orphan*/  nmc_left; int /*<<< orphan*/  nmc_mcur; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ mbuf_data (int /*<<< orphan*/ ) ; 
 int nfsm_chain_advance (struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_dissect_init (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsm_chain_offset (struct nfsm_chain*) ; 

int
nfsm_chain_reverse(struct nfsm_chain *nmc, uint32_t len)
{
	uint32_t mlen, new_offset;
	int error = 0;

	mlen = nmc->nmc_ptr - (caddr_t) mbuf_data(nmc->nmc_mcur);
	if (len <= mlen) {
		nmc->nmc_ptr -= len;
		nmc->nmc_left += len;
		return (0);
	}

	new_offset = nfsm_chain_offset(nmc) - len;
	nfsm_chain_dissect_init(error, nmc, nmc->nmc_mhead);
	if (error)
		return (error);

	return (nfsm_chain_advance(nmc, new_offset));
}