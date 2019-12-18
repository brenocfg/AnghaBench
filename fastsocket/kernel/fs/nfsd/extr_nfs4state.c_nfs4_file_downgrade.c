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
struct nfs4_stateid {int /*<<< orphan*/  st_access_bmap; int /*<<< orphan*/  st_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_access_to_omode (int) ; 
 int /*<<< orphan*/  nfs4_file_put_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nfs4_file_downgrade(struct nfs4_stateid *stp, unsigned int to_access)
{
	int i;

	for (i = 1; i < 4; i++) {
		if (test_bit(i, &stp->st_access_bmap)
					&& ((i & to_access) != i)) {
			nfs4_file_put_access(stp->st_file, nfs4_access_to_omode(i));
			__clear_bit(i, &stp->st_access_bmap);
		}
	}
}