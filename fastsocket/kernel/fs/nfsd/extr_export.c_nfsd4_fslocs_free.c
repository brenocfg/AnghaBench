#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_fs_locations {int locations_count; TYPE_1__* locations; } ;
struct TYPE_2__ {struct TYPE_2__* hosts; struct TYPE_2__* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void nfsd4_fslocs_free(struct nfsd4_fs_locations *fsloc)
{
	int i;

	for (i = 0; i < fsloc->locations_count; i++) {
		kfree(fsloc->locations[i].path);
		kfree(fsloc->locations[i].hosts);
	}
	kfree(fsloc->locations);
}