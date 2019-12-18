#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct nfsd4_sequence {int /*<<< orphan*/  maxslots; int /*<<< orphan*/  slotid; int /*<<< orphan*/  seqid; TYPE_1__ sessionid; } ;
struct TYPE_4__ {int* datap; } ;
struct nfsd4_compoundres {TYPE_2__ cstate; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 scalar_t__ NFS4_MAX_SESSIONID_LEN ; 
 int /*<<< orphan*/  RESERVE_SPACE (scalar_t__) ; 
 int /*<<< orphan*/  WRITE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITEMEM (int /*<<< orphan*/ ,scalar_t__) ; 

__be32
nfsd4_encode_sequence(struct nfsd4_compoundres *resp, int nfserr,
		      struct nfsd4_sequence *seq)
{
	__be32 *p;

	if (nfserr)
		return nfserr;

	RESERVE_SPACE(NFS4_MAX_SESSIONID_LEN + 20);
	WRITEMEM(seq->sessionid.data, NFS4_MAX_SESSIONID_LEN);
	WRITE32(seq->seqid);
	WRITE32(seq->slotid);
	WRITE32(seq->maxslots);
	/*
	 * FIXME: for now:
	 *   target_maxslots = maxslots
	 *   status_flags = 0
	 */
	WRITE32(seq->maxslots);
	WRITE32(0);

	ADJUST_ARGS();
	resp->cstate.datap = p; /* DRC cache data pointer */
	return 0;
}