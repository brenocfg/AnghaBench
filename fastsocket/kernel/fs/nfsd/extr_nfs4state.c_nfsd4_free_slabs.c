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

/* Variables and functions */
 int /*<<< orphan*/  deleg_slab ; 
 int /*<<< orphan*/  file_slab ; 
 int /*<<< orphan*/  nfsd4_free_slab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stateid_slab ; 
 int /*<<< orphan*/  stateowner_slab ; 

void
nfsd4_free_slabs(void)
{
	nfsd4_free_slab(&stateowner_slab);
	nfsd4_free_slab(&file_slab);
	nfsd4_free_slab(&stateid_slab);
	nfsd4_free_slab(&deleg_slab);
}