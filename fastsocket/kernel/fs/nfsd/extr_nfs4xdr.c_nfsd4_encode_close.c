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
struct nfsd4_compoundres {int dummy; } ;
struct nfsd4_close {int /*<<< orphan*/  cl_stateowner; int /*<<< orphan*/  cl_stateid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_SEQID_OP_HEAD ; 
 int /*<<< orphan*/  ENCODE_SEQID_OP_TAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_encode_stateid (struct nfsd4_compoundres*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_encode_close(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_close *close)
{
	ENCODE_SEQID_OP_HEAD;

	if (!nfserr)
		nfsd4_encode_stateid(resp, &close->cl_stateid);

	ENCODE_SEQID_OP_TAIL(close->cl_stateowner);
	return nfserr;
}