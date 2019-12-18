#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* page; } ;
typedef  TYPE_1__ nfs_readdir_descriptor_t ;
struct TYPE_6__ {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_readdir_clear_array (TYPE_2__*) ; 
 int /*<<< orphan*/  page_cache_release (TYPE_2__*) ; 

__attribute__((used)) static
void cache_page_release(nfs_readdir_descriptor_t *desc)
{
	if (!desc->page->mapping)
		nfs_readdir_clear_array(desc->page);
	page_cache_release(desc->page);
	desc->page = NULL;
}