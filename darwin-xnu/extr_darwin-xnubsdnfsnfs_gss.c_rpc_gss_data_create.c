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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nfsm_chain {int /*<<< orphan*/  nmc_mhead; int /*<<< orphan*/  nmc_mcur; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int errno_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MBUF_TYPE_DATA ; 
 int /*<<< orphan*/  MBUF_WAITOK ; 
 int /*<<< orphan*/ * mbuf_data (int /*<<< orphan*/ ) ; 
 int mbuf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mbuf_setdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_setnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_init (struct nfsm_chain*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
rpc_gss_data_create(mbuf_t *mbp_head, uint32_t seqnum)
{
	int error;
	mbuf_t mb;
	struct nfsm_chain nmc;
	struct nfsm_chain *nmcp = &nmc;
	uint8_t *data;

	error = mbuf_get(MBUF_WAITOK, MBUF_TYPE_DATA, &mb);
	if (error)
		return (error);
	data = mbuf_data(mb);
#if 0
	/* Reserve space for prepending */
	len = mbuf_maxlen(mb);
	len = (len & ~0x3) - NFSX_UNSIGNED;
	printf("%s: data = %p, len = %d\n", __func__, data, (int)len);
	error = mbuf_setdata(mb, data + len, 0);
	if (error || mbuf_trailingspace(mb))
		printf("%s: data = %p trailingspace = %d error = %d\n", __func__, mbuf_data(mb), (int)mbuf_trailingspace(mb), error);
#endif
	/* Reserve 16 words for prepending */
	error = mbuf_setdata(mb, data + 16*sizeof(uint32_t), 0);
	nfsm_chain_init(nmcp, mb);
	nfsm_chain_add_32(error, nmcp, seqnum);
	nfsm_chain_build_done(error, nmcp);
	if (error)
		return (EINVAL);
	mbuf_setnext(nmcp->nmc_mcur, *mbp_head);
	*mbp_head = nmcp->nmc_mhead;

	return (0);
}