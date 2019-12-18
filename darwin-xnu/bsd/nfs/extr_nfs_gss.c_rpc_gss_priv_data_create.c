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
struct nfsm_chain {int dummy; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ NFSX_UNSIGNED ; 
 scalar_t__ gss_krb5_wrap_mbuf (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_gss_mchain_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_opaque_nopad (scalar_t__,struct nfsm_chain*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_adv (scalar_t__,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (scalar_t__,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_dissect_init (scalar_t__,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_finish_mbuf (scalar_t__,struct nfsm_chain*) ; 
 scalar_t__ nfsm_pad (scalar_t__) ; 
 scalar_t__ rpc_gss_data_create (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ rpc_gss_prepend_32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xdrpad ; 

__attribute__((used)) static errno_t
rpc_gss_priv_data_create(gss_ctx_id_t ctx, mbuf_t *mb_head, uint32_t seqnum, uint32_t *len)
{
	uint32_t error;
	uint32_t major;
	struct nfsm_chain nmc;
	uint32_t pad;
	uint32_t length;

	error = rpc_gss_data_create(mb_head, seqnum);
	if (error)
		return (error);

	length = nfs_gss_mchain_length(*mb_head);
	major = gss_krb5_wrap_mbuf(&error, ctx, 1, 0, mb_head, 0, length, NULL);
	if (major != GSS_S_COMPLETE)
		return (error);

	length = nfs_gss_mchain_length(*mb_head);
	if (len)
		*len = length;
	pad = nfsm_pad(length);

	/* Prepend the opaque length of rep rpc_gss_priv_data */
	error = rpc_gss_prepend_32(mb_head, length);

	if (error)
		return (error);
	if (pad) {
		nfsm_chain_dissect_init(error, &nmc, *mb_head);
		/* Advance the opauque size of length and length data */
		nfsm_chain_adv(error, &nmc, NFSX_UNSIGNED + length);
		nfsm_chain_finish_mbuf(error, &nmc);
		nfsm_chain_add_opaque_nopad(error, &nmc, xdrpad, pad);
		nfsm_chain_build_done(error, &nmc);
	}

	return (error);
}