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
typedef  int /*<<< orphan*/  u_char ;
struct nfsm_chain {int /*<<< orphan*/  nmc_left; int /*<<< orphan*/ * nmc_ptr; scalar_t__ nmc_mcur; } ;
typedef  scalar_t__ mbuf_t ;

/* Variables and functions */
 int EBADRPC ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * mbuf_data (scalar_t__) ; 
 int /*<<< orphan*/  mbuf_len (scalar_t__) ; 
 scalar_t__ mbuf_next (scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_adv (int,struct nfsm_chain*,scalar_t__) ; 
 scalar_t__ nfsm_rndup (scalar_t__) ; 

int
nfsm_chain_get_opaque_f(struct nfsm_chain *nmc, uint32_t len, u_char *buf)
{
	uint32_t cplen, padlen;
	int error = 0;

	padlen = nfsm_rndup(len) - len;

	/* loop through mbufs copying all the data we need */
	while (len && nmc->nmc_mcur) {
		/* copy as much as we need/can */
		cplen = MIN(nmc->nmc_left, len);
		if (cplen) {
			bcopy(nmc->nmc_ptr, buf, cplen);
			nmc->nmc_ptr += cplen;
			nmc->nmc_left -= cplen;
			buf += cplen;
			len -= cplen;
		}
		/* if more needed, go to next mbuf */
		if (len) {
			mbuf_t mb = mbuf_next(nmc->nmc_mcur);
			nmc->nmc_mcur = mb;
			nmc->nmc_ptr = mb ? mbuf_data(mb) : NULL;
			nmc->nmc_left = mb ? mbuf_len(mb) : 0;
		}
	}

	/* did we run out of data in the mbuf chain? */
	if (len)
		return (EBADRPC);

	if (padlen)
		nfsm_chain_adv(error, nmc, padlen);

	return (error);
}