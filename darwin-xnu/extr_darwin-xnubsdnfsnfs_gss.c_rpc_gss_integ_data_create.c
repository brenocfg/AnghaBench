#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct nfsm_chain {int /*<<< orphan*/  nmc_mhead; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ NFSX_UNSIGNED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ gss_krb5_get_mic_mbuf (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ nfs_gss_mchain_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (scalar_t__,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_opaque (scalar_t__,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_adv (scalar_t__,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (scalar_t__,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_dissect_init (scalar_t__,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_finish_mbuf (scalar_t__,struct nfsm_chain*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ rpc_gss_data_create (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ rpc_gss_prepend_32 (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static errno_t
rpc_gss_integ_data_create(gss_ctx_id_t ctx, mbuf_t *mb_head, uint32_t seqnum, uint32_t *len)
{
	uint32_t error;
	uint32_t major;
	uint32_t length;
	gss_buffer_desc mic;
	struct nfsm_chain nmc;

	/* Length of the argument or result */
	length = nfs_gss_mchain_length(*mb_head);
	if (len)
		*len = length;
	error = rpc_gss_data_create(mb_head, seqnum);
	if (error)
		return (error);

	/*
	 * length is the length of the rpc_gss_data
	 */
	length += NFSX_UNSIGNED;  /* Add the sequence number to the length */
	major = gss_krb5_get_mic_mbuf(&error, ctx, 0, *mb_head, 0, length, &mic);
	if (major != GSS_S_COMPLETE) {
		printf("gss_krb5_get_mic_mbuf failed %d\n", error);
		return (error);
	}

	error = rpc_gss_prepend_32(mb_head, length);
	if (error)
		return (error);

	nfsm_chain_dissect_init(error, &nmc, *mb_head);
	/* Append GSS mic token by advancing rpc_gss_data_t length + NFSX_UNSIGNED (size of the length field) */
	nfsm_chain_adv(error, &nmc, length + NFSX_UNSIGNED);
	nfsm_chain_finish_mbuf(error, &nmc); // Force the mic into its own sub chain.
	nfsm_chain_add_32(error, &nmc, mic.length);
	nfsm_chain_add_opaque(error, &nmc, mic.value, mic.length);
	nfsm_chain_build_done(error, &nmc);
	gss_release_buffer(NULL, &mic);

//	printmbuf("rpc_gss_integ_data_create done", *mb_head, 0, 0);
	assert(nmc.nmc_mhead == *mb_head);

	return (error);
}