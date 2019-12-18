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
struct nfsd4_lockt {int /*<<< orphan*/  lt_denied; } ;
struct nfsd4_compoundres {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_encode_lock_denied (struct nfsd4_compoundres*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfserr_denied ; 

__attribute__((used)) static __be32
nfsd4_encode_lockt(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_lockt *lockt)
{
	if (nfserr == nfserr_denied)
		nfsd4_encode_lock_denied(resp, &lockt->lt_denied);
	return nfserr;
}