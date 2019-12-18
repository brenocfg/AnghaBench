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
struct TYPE_3__ {struct sg_list* data; } ;
struct splice_desc {unsigned int len; unsigned int pos; TYPE_1__ u; } ;
struct sg_list {size_t n; size_t size; unsigned int len; int /*<<< orphan*/ * sg; } ;
struct pipe_inode_info {int dummy; } ;
struct pipe_buffer {unsigned int offset; TYPE_2__* ops; struct page* page; int /*<<< orphan*/  len; } ;
struct page {int dummy; } ;
struct TYPE_4__ {scalar_t__ (* steal ) (struct pipe_inode_info*,struct pipe_buffer*) ;char* (* map ) (struct pipe_inode_info*,struct pipe_buffer*,int) ;int /*<<< orphan*/  (* unmap ) (struct pipe_inode_info*,struct pipe_buffer*,char*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SIZE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,struct page*,unsigned int,unsigned int) ; 
 scalar_t__ stub1 (struct pipe_inode_info*,struct pipe_buffer*) ; 
 char* stub2 (struct pipe_inode_info*,struct pipe_buffer*,int) ; 
 int /*<<< orphan*/  stub3 (struct pipe_inode_info*,struct pipe_buffer*,char*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int pipe_to_sg(struct pipe_inode_info *pipe, struct pipe_buffer *buf,
			struct splice_desc *sd)
{
	struct sg_list *sgl = sd->u.data;
	unsigned int offset, len;

	if (sgl->n == sgl->size)
		return 0;

	/* Try lock this page */
	if (buf->ops->steal(pipe, buf) == 0) {
		/* Get reference and unlock page for moving */
		get_page(buf->page);
		unlock_page(buf->page);

		len = min(buf->len, sd->len);
		sg_set_page(&(sgl->sg[sgl->n]), buf->page, len, buf->offset);
	} else {
		/* Failback to copying a page */
		struct page *page = alloc_page(GFP_KERNEL);
		char *src = buf->ops->map(pipe, buf, 1);
		char *dst;

		if (!page)
			return -ENOMEM;
		dst = kmap(page);

		offset = sd->pos & ~PAGE_MASK;

		len = sd->len;
		if (len + offset > PAGE_SIZE)
			len = PAGE_SIZE - offset;

		memcpy(dst + offset, src + buf->offset, len);

		kunmap(page);
		buf->ops->unmap(pipe, buf, src);

		sg_set_page(&(sgl->sg[sgl->n]), page, len, offset);
	}
	sgl->n++;
	sgl->len += len;

	return len;
}