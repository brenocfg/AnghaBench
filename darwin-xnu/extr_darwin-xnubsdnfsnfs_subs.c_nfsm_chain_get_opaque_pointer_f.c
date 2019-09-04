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
struct nfsm_chain {void* nmc_mcur; scalar_t__ nmc_left; int /*<<< orphan*/ * nmc_ptr; } ;
typedef  void* mbuf_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int EBADRPC ; 
 int EOVERFLOW ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 void* mbuf_data (void*) ; 
 int /*<<< orphan*/  mbuf_free (void*) ; 
 scalar_t__ mbuf_len (void*) ; 
 scalar_t__ mbuf_maxlen (void*) ; 
 void* mbuf_next (void*) ; 
 int mbuf_setdata (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mbuf_setlen (void*,scalar_t__) ; 
 int mbuf_setnext (void*,void*) ; 
 scalar_t__ mbuf_trailingspace (void*) ; 
 int nfsm_chain_advance (struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_mbuf_get (int,void**,scalar_t__) ; 
 scalar_t__ nfsm_rndup (scalar_t__) ; 

int
nfsm_chain_get_opaque_pointer_f(struct nfsm_chain *nmc, uint32_t len, u_char **pptr)
{
	mbuf_t mbcur, mb;
	uint32_t left, need, mblen, cplen, padlen;
	u_char *ptr;
	int error = 0;

	/* move to next mbuf with data */
	while (nmc->nmc_mcur && (nmc->nmc_left == 0)) {
		mb = mbuf_next(nmc->nmc_mcur);
		nmc->nmc_mcur = mb;
		if (!mb)
			break;
		nmc->nmc_ptr = mbuf_data(mb);
		nmc->nmc_left = mbuf_len(mb);
	}
	/* check if we've run out of data */
	if (!nmc->nmc_mcur)
		return (EBADRPC);

	/* do we already have a contiguous buffer? */
	if (nmc->nmc_left >= len) {
		/* the returned pointer will be the current pointer */
		*pptr = (u_char*)nmc->nmc_ptr;
		error = nfsm_chain_advance(nmc, nfsm_rndup(len));
		return (error);
	}

	padlen = nfsm_rndup(len) - len;

	/* we need (len - left) more bytes */
	mbcur = nmc->nmc_mcur;
	left = nmc->nmc_left;
	need = len - left;

	if (need > mbuf_trailingspace(mbcur)) {
		/*
		 * The needed bytes won't fit in the current mbuf so we'll
		 * allocate a new mbuf to hold the contiguous range of data.
		 */
		nfsm_mbuf_get(error, &mb, len);
		if (error)
			return (error);
		/* double check that this mbuf can hold all the data */
		if (mbuf_maxlen(mb) < len) {
			mbuf_free(mb);
			return (EOVERFLOW);
		}

		/* the returned pointer will be the new mbuf's data pointer */
		*pptr = ptr = mbuf_data(mb);

		/* copy "left" bytes to the new mbuf */
		bcopy(nmc->nmc_ptr, ptr, left);
		ptr += left;
		mbuf_setlen(mb, left);

		/* insert the new mbuf between the current and next mbufs */
		error = mbuf_setnext(mb, mbuf_next(mbcur));
		if (!error)
			error = mbuf_setnext(mbcur, mb);
		if (error) {
			mbuf_free(mb);
			return (error);
		}

		/* reduce current mbuf's length by "left" */
		mbuf_setlen(mbcur, mbuf_len(mbcur) - left);

		/*
		 * update nmc's state to point at the end of the mbuf
		 * where the needed data will be copied to.
		 */
		nmc->nmc_mcur = mbcur = mb;
		nmc->nmc_left = 0;
		nmc->nmc_ptr = (caddr_t)ptr;
	} else {
		/* The rest of the data will fit in this mbuf. */

		/* the returned pointer will be the current pointer */
		*pptr = (u_char*)nmc->nmc_ptr;

		/*
		 * update nmc's state to point at the end of the mbuf
		 * where the needed data will be copied to.
		 */
		nmc->nmc_ptr += left;
		nmc->nmc_left = 0;
	}

	/*
	 * move the next "need" bytes into the current
	 * mbuf from the mbufs that follow
	 */

	/* extend current mbuf length */
	mbuf_setlen(mbcur, mbuf_len(mbcur) + need);

	/* mb follows mbufs we're copying/compacting data from */
	mb = mbuf_next(mbcur);

	while (need && mb) {
		/* copy as much as we need/can */
		ptr = mbuf_data(mb);
		mblen = mbuf_len(mb);
		cplen = MIN(mblen, need);
		if (cplen) {
			bcopy(ptr, nmc->nmc_ptr, cplen);
			/*
			 * update the mbuf's pointer and length to reflect that
			 * the data was shifted to an earlier mbuf in the chain
			 */
			error = mbuf_setdata(mb, ptr + cplen, mblen - cplen);
			if (error) {
				mbuf_setlen(mbcur, mbuf_len(mbcur) - need);
				return (error);
			}
			/* update pointer/need */
			nmc->nmc_ptr += cplen;
			need -= cplen;
		}
		/* if more needed, go to next mbuf */
		if (need)
			mb = mbuf_next(mb);
	}

	/* did we run out of data in the mbuf chain? */
	if (need) {
		mbuf_setlen(mbcur, mbuf_len(mbcur) - need);
		return (EBADRPC);
	}

	/*
	 * update nmc's state to point after this contiguous data
	 *
	 * "mb" points to the last mbuf we copied data from so we
	 * just set nmc to point at whatever remains in that mbuf.
	 */
	nmc->nmc_mcur = mb;
	nmc->nmc_ptr = mbuf_data(mb);
	nmc->nmc_left = mbuf_len(mb);

	/* move past any padding */
	if (padlen)
		error = nfsm_chain_advance(nmc, padlen);

	return (error);
}