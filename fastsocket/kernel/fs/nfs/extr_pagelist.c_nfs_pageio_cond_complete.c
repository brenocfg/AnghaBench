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
struct TYPE_2__ {int /*<<< orphan*/  prev; } ;
struct nfs_pageio_descriptor {TYPE_1__ pg_list; } ;
struct nfs_page {scalar_t__ wb_index; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 

void nfs_pageio_cond_complete(struct nfs_pageio_descriptor *desc, pgoff_t index)
{
	if (!list_empty(&desc->pg_list)) {
		struct nfs_page *prev = nfs_list_entry(desc->pg_list.prev);
		if (index != prev->wb_index + 1)
			nfs_pageio_complete(desc);
	}
}