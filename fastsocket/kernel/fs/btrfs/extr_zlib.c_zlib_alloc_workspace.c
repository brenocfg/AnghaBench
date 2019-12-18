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
struct list_head {int dummy; } ;
struct TYPE_4__ {void* workspace; } ;
struct TYPE_3__ {void* workspace; } ;
struct workspace {struct list_head list; int /*<<< orphan*/  buf; TYPE_2__ inf_strm; TYPE_1__ def_strm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct list_head* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct workspace* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* vmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_deflate_workspacesize () ; 
 int /*<<< orphan*/  zlib_free_workspace (struct list_head*) ; 
 int /*<<< orphan*/  zlib_inflate_workspacesize () ; 

__attribute__((used)) static struct list_head *zlib_alloc_workspace(void)
{
	struct workspace *workspace;

	workspace = kzalloc(sizeof(*workspace), GFP_NOFS);
	if (!workspace)
		return ERR_PTR(-ENOMEM);

	workspace->def_strm.workspace = vmalloc(zlib_deflate_workspacesize());
	workspace->inf_strm.workspace = vmalloc(zlib_inflate_workspacesize());
	workspace->buf = kmalloc(PAGE_CACHE_SIZE, GFP_NOFS);
	if (!workspace->def_strm.workspace ||
	    !workspace->inf_strm.workspace || !workspace->buf)
		goto fail;

	INIT_LIST_HEAD(&workspace->list);

	return &workspace->list;
fail:
	zlib_free_workspace(&workspace->list);
	return ERR_PTR(-ENOMEM);
}