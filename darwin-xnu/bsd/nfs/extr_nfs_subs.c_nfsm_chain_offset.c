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
struct nfsm_chain {scalar_t__ nmc_mhead; scalar_t__ nmc_mcur; int nmc_ptr; } ;
typedef  scalar_t__ mbuf_t ;
typedef  int caddr_t ;

/* Variables and functions */
 scalar_t__ mbuf_data (scalar_t__) ; 
 scalar_t__ mbuf_len (scalar_t__) ; 
 scalar_t__ mbuf_next (scalar_t__) ; 

int
nfsm_chain_offset(struct nfsm_chain *nmc)
{
	mbuf_t mb;
	int len = 0;

	for (mb = nmc->nmc_mhead; mb; mb = mbuf_next(mb)) {
		if (mb == nmc->nmc_mcur)
			return (len + (nmc->nmc_ptr - (caddr_t) mbuf_data(mb)));
		len += mbuf_len(mb);
	}

	return (len);
}