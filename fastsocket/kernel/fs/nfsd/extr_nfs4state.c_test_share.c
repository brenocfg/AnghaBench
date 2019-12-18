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
struct nfsd4_open {unsigned int op_share_deny; unsigned int op_share_access; } ;
struct nfs4_stateid {int /*<<< orphan*/  st_deny_bmap; int /*<<< orphan*/  st_access_bmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_access (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_deny (unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
test_share(struct nfs4_stateid *stp, struct nfsd4_open *open) {
	unsigned int access, deny;

	set_access(&access, stp->st_access_bmap);
	set_deny(&deny, stp->st_deny_bmap);
	if ((access & open->op_share_deny) || (deny & open->op_share_access))
		return 0;
	return 1;
}