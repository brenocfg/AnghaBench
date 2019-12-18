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
typedef  int /*<<< orphan*/  uio_t ;
typedef  scalar_t__ uint32_t ;
struct nfsm_chain {scalar_t__ nmc_left; int /*<<< orphan*/  nmc_ptr; } ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,scalar_t__) ; 
 int nfsm_chain_new_mbuf (struct nfsm_chain*,scalar_t__) ; 
 scalar_t__ nfsm_rndup (scalar_t__) ; 
 int /*<<< orphan*/  uiomove (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int
nfsm_chain_add_uio(struct nfsm_chain *nmc, uio_t uio, uint32_t len)
{
	uint32_t paddedlen, tlen;
	int error;

	paddedlen = nfsm_rndup(len);

	while (paddedlen) {
		if (!nmc->nmc_left) {
			error = nfsm_chain_new_mbuf(nmc, paddedlen);
			if (error)
				return (error);
		}
		tlen = MIN(nmc->nmc_left, paddedlen);
		if (tlen) {
			if (len) {
				if (tlen > len)
					tlen = len;
				uiomove(nmc->nmc_ptr, tlen, uio);
			} else {
				bzero(nmc->nmc_ptr, tlen);
			}
			nmc->nmc_ptr += tlen;
			nmc->nmc_left -= tlen;
			paddedlen -= tlen;
			if (len)
				len -= tlen;
		}
	}
	return (0);
}