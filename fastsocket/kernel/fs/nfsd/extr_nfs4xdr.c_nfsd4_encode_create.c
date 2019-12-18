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
struct nfsd4_create {int* cr_bmval; int /*<<< orphan*/  cr_cinfo; } ;
struct nfsd4_compoundres {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int /*<<< orphan*/  RESERVE_SPACE (int) ; 
 int /*<<< orphan*/  WRITE32 (int) ; 
 int /*<<< orphan*/  write_cinfo (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_encode_create(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_create *create)
{
	__be32 *p;

	if (!nfserr) {
		RESERVE_SPACE(32);
		write_cinfo(&p, &create->cr_cinfo);
		WRITE32(2);
		WRITE32(create->cr_bmval[0]);
		WRITE32(create->cr_bmval[1]);
		ADJUST_ARGS();
	}
	return nfserr;
}