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
typedef  int /*<<< orphan*/  u_int64_t ;
struct mptcb {scalar_t__ mpt_version; scalar_t__ mpt_remote_idsn; scalar_t__ mpt_rcvnxt; int /*<<< orphan*/  mpt_remotetoken; int /*<<< orphan*/  mpt_remotekey; int /*<<< orphan*/  mpt_mpte; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ MPTCP_STD_VERSION_0 ; 
 int SHA1_RESULTLEN ; 
 int /*<<< orphan*/  mptcp_do_sha1 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mptcp_generate_idsn (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mptcp_generate_token (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpte_lock_assert_held (int /*<<< orphan*/ ) ; 

int
mptcp_init_remote_parms(struct mptcb *mp_tp)
{
	char remote_digest[SHA1_RESULTLEN];
	mpte_lock_assert_held(mp_tp->mpt_mpte);

	/* Only Version 0 is supported for auth purposes */
	if (mp_tp->mpt_version != MPTCP_STD_VERSION_0)
		return (-1);

	/* Setup local and remote tokens and Initial DSNs */
	mptcp_do_sha1(&mp_tp->mpt_remotekey, remote_digest);
	mptcp_generate_token(remote_digest, SHA1_RESULTLEN,
	    (caddr_t)&mp_tp->mpt_remotetoken, sizeof (mp_tp->mpt_remotetoken));
	mptcp_generate_idsn(remote_digest, SHA1_RESULTLEN,
	    (caddr_t)&mp_tp->mpt_remote_idsn, sizeof (u_int64_t));
	mp_tp->mpt_rcvnxt = mp_tp->mpt_remote_idsn + 1;

	return (0);
}