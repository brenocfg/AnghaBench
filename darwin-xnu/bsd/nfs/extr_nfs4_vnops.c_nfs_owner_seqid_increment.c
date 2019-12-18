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
struct nfs_open_owner {int /*<<< orphan*/  noo_seqid; } ;
struct nfs_lock_owner {int /*<<< orphan*/  nlo_seqid; } ;

/* Variables and functions */
#define  NFSERR_BADXDR 135 
#define  NFSERR_BAD_SEQID 134 
#define  NFSERR_BAD_STATEID 133 
#define  NFSERR_NOFILEHANDLE 132 
#define  NFSERR_OLD_STATEID 131 
#define  NFSERR_RESOURCE 130 
#define  NFSERR_STALE_CLIENTID 129 
#define  NFSERR_STALE_STATEID 128 

void
nfs_owner_seqid_increment(struct nfs_open_owner *noop, struct nfs_lock_owner *nlop, int error)
{
	switch (error) {
	case NFSERR_STALE_CLIENTID:
	case NFSERR_STALE_STATEID:
	case NFSERR_OLD_STATEID:
	case NFSERR_BAD_STATEID:
	case NFSERR_BAD_SEQID:
	case NFSERR_BADXDR:
	case NFSERR_RESOURCE:
	case NFSERR_NOFILEHANDLE:
		/* do not increment the open seqid on these errors */
		return;
	}
	if (noop)
		noop->noo_seqid++;
	if (nlop)
		nlop->nlo_seqid++;
}