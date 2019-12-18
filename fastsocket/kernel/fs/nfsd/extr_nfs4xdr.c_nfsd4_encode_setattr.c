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
struct nfsd4_setattr {int* sa_bmval; } ;
struct nfsd4_compoundres {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int /*<<< orphan*/  RESERVE_SPACE (int) ; 
 int /*<<< orphan*/  WRITE32 (int) ; 

__attribute__((used)) static __be32
nfsd4_encode_setattr(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_setattr *setattr)
{
	__be32 *p;

	RESERVE_SPACE(12);
	if (nfserr) {
		WRITE32(2);
		WRITE32(0);
		WRITE32(0);
	}
	else {
		WRITE32(2);
		WRITE32(setattr->sa_bmval[0]);
		WRITE32(setattr->sa_bmval[1]);
	}
	ADJUST_ARGS();
	return nfserr;
}