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
struct list_head {int dummy; } ;
struct workspace {struct list_head list; void* cbuf; void* buf; void* mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct list_head* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  LZO1X_MEM_COMPRESS ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 struct workspace* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzo1x_worst_compress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzo_free_workspace (struct list_head*) ; 
 void* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct list_head *lzo_alloc_workspace(void)
{
	struct workspace *workspace;

	workspace = kzalloc(sizeof(*workspace), GFP_NOFS);
	if (!workspace)
		return ERR_PTR(-ENOMEM);

	workspace->mem = vmalloc(LZO1X_MEM_COMPRESS);
	workspace->buf = vmalloc(lzo1x_worst_compress(PAGE_CACHE_SIZE));
	workspace->cbuf = vmalloc(lzo1x_worst_compress(PAGE_CACHE_SIZE));
	if (!workspace->mem || !workspace->buf || !workspace->cbuf)
		goto fail;

	INIT_LIST_HEAD(&workspace->list);

	return &workspace->list;
fail:
	lzo_free_workspace(&workspace->list);
	return ERR_PTR(-ENOMEM);
}