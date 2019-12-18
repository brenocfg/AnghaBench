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
struct nfsd4_compoundargs {int dummy; } ;
struct nfsd4_close {int /*<<< orphan*/  cl_stateid; int /*<<< orphan*/  cl_seqid; int /*<<< orphan*/ * cl_stateowner; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  nfsd4_decode_stateid (struct nfsd4_compoundargs*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_decode_close(struct nfsd4_compoundargs *argp, struct nfsd4_close *close)
{
	DECODE_HEAD;

	close->cl_stateowner = NULL;
	READ_BUF(4);
	READ32(close->cl_seqid);
	return nfsd4_decode_stateid(argp, &close->cl_stateid);

	DECODE_TAIL;
}