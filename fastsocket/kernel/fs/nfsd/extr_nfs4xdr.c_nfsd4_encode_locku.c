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
struct nfsd4_locku {int /*<<< orphan*/  lu_stateowner; int /*<<< orphan*/  lu_stateid; } ;
struct nfsd4_compoundres {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_SEQID_OP_HEAD ; 
 int /*<<< orphan*/  ENCODE_SEQID_OP_TAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_encode_stateid (struct nfsd4_compoundres*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_encode_locku(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_locku *locku)
{
	ENCODE_SEQID_OP_HEAD;

	if (!nfserr)
		nfsd4_encode_stateid(resp, &locku->lu_stateid);

	ENCODE_SEQID_OP_TAIL(locku->lu_stateowner);
	return nfserr;
}