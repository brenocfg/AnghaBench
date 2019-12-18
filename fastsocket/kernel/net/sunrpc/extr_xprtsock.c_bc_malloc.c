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
struct rpc_task {int dummy; } ;
struct rpc_buffer {int len; void* data; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 struct rpc_buffer* page_address (struct page*) ; 

void *bc_malloc(struct rpc_task *task, size_t size)
{
	struct page *page;
	struct rpc_buffer *buf;

	BUG_ON(size > PAGE_SIZE - sizeof(struct rpc_buffer));
	page = alloc_page(GFP_KERNEL);

	if (!page)
		return NULL;

	buf = page_address(page);
	buf->len = PAGE_SIZE;

	return buf->data;
}