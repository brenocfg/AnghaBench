#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pgnum; } ;
struct nandsim {TYPE_2__* pages; int /*<<< orphan*/  nand_pages_slab; TYPE_1__ geom; scalar_t__ cfile; TYPE_2__* pages_written; int /*<<< orphan*/  file_buf; } ;
struct TYPE_4__ {scalar_t__ byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  filp_close (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vfree (TYPE_2__*) ; 

__attribute__((used)) static void free_device(struct nandsim *ns)
{
	int i;

	if (ns->cfile) {
		kfree(ns->file_buf);
		vfree(ns->pages_written);
		filp_close(ns->cfile, NULL);
		return;
	}

	if (ns->pages) {
		for (i = 0; i < ns->geom.pgnum; i++) {
			if (ns->pages[i].byte)
				kmem_cache_free(ns->nand_pages_slab,
						ns->pages[i].byte);
		}
		kmem_cache_destroy(ns->nand_pages_slab);
		vfree(ns->pages);
	}
}