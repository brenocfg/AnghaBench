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
struct nfs4_stateid {int /*<<< orphan*/  st_file; int /*<<< orphan*/  st_access_bmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_stateid*) ; 
 int /*<<< orphan*/  nfs4_access_to_omode (int) ; 
 int /*<<< orphan*/  nfs4_file_put_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_nfs4_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stateid_slab ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_generic_stateid(struct nfs4_stateid *stp)
{
	int i;

	if (stp->st_access_bmap) {
		for (i = 1; i < 4; i++) {
			if (test_bit(i, &stp->st_access_bmap))
				nfs4_file_put_access(stp->st_file,
						nfs4_access_to_omode(i));
		}
	}
	put_nfs4_file(stp->st_file);
	kmem_cache_free(stateid_slab, stp);
}