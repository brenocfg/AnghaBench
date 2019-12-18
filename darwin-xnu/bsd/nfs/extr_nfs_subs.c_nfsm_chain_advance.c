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
struct nfsm_chain {scalar_t__ nmc_left; int /*<<< orphan*/  nmc_ptr; int /*<<< orphan*/  nmc_mcur; } ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */
 int EBADRPC ; 
 int /*<<< orphan*/  mbuf_data (int /*<<< orphan*/ ) ; 
 scalar_t__ mbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_next (int /*<<< orphan*/ ) ; 

int
nfsm_chain_advance(struct nfsm_chain *nmc, uint32_t len)
{
	mbuf_t mb;

	while (len) {
		if (nmc->nmc_left >= len) {
			nmc->nmc_left -= len;
			nmc->nmc_ptr += len;
			return (0);
		}
		len -= nmc->nmc_left;
		nmc->nmc_mcur = mb = mbuf_next(nmc->nmc_mcur);
		if (!mb)
			return (EBADRPC);
		nmc->nmc_ptr = mbuf_data(mb);
		nmc->nmc_left = mbuf_len(mb);
	}

	return (0);
}