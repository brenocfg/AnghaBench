#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  page_index; TYPE_4__* file; } ;
typedef  TYPE_5__ nfs_readdir_descriptor_t ;
typedef  int /*<<< orphan*/  filler_t ;
struct TYPE_10__ {TYPE_2__* dentry; } ;
struct TYPE_11__ {TYPE_3__ f_path; } ;
struct TYPE_9__ {TYPE_1__* d_inode; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 scalar_t__ nfs_readdir_filler ; 
 struct page* read_cache_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static
struct page *get_cache_page(nfs_readdir_descriptor_t *desc)
{
	return read_cache_page(desc->file->f_path.dentry->d_inode->i_mapping,
			desc->page_index, (filler_t *)nfs_readdir_filler, desc);
}