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
struct nfs_server {int caps; } ;
typedef  enum open_claim_type4 { ____Placeholder_open_claim_type4 } open_claim_type4 ;

/* Variables and functions */
 int NFS4_OPEN_CLAIM_DELEGATE_CUR ; 
 int NFS4_OPEN_CLAIM_DELEGATE_PREV ; 
#define  NFS4_OPEN_CLAIM_DELEG_CUR_FH 130 
#define  NFS4_OPEN_CLAIM_DELEG_PREV_FH 129 
#define  NFS4_OPEN_CLAIM_FH 128 
 int NFS4_OPEN_CLAIM_NULL ; 
 int NFS_CAP_ATOMIC_OPEN_V1 ; 

__attribute__((used)) static enum open_claim_type4
nfs4_map_atomic_open_claim(struct nfs_server *server,
		enum open_claim_type4 claim)
{
	if (server->caps & NFS_CAP_ATOMIC_OPEN_V1)
		return claim;
	switch (claim) {
	default:
		return claim;
	case NFS4_OPEN_CLAIM_FH:
		return NFS4_OPEN_CLAIM_NULL;
	case NFS4_OPEN_CLAIM_DELEG_CUR_FH:
		return NFS4_OPEN_CLAIM_DELEGATE_CUR;
	case NFS4_OPEN_CLAIM_DELEG_PREV_FH:
		return NFS4_OPEN_CLAIM_DELEGATE_PREV;
	}
}