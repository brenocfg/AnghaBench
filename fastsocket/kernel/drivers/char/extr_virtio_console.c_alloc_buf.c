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
struct virtqueue {int dummy; } ;
struct scatterlist {int dummy; } ;
struct port_buffer {int sgpages; size_t size; scalar_t__ offset; scalar_t__ len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct port_buffer*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct port_buffer *alloc_buf(struct virtqueue *vq, size_t buf_size,
				     int pages)
{
	struct port_buffer *buf;

	/*
	 * Allocate buffer and the sg list. The sg list array is allocated
	 * directly after the port_buffer struct.
	 */
	buf = kmalloc(sizeof(*buf) + sizeof(struct scatterlist) * pages,
		      GFP_KERNEL);
	if (!buf)
		goto fail;

	buf->sgpages = pages;
	if (pages > 0) {
		buf->buf = NULL;
		return buf;
	}

	buf->buf = kmalloc(buf_size, GFP_KERNEL);
	if (!buf->buf)
		goto free_buf;
	buf->len = 0;
	buf->offset = 0;
	buf->size = buf_size;
	return buf;

free_buf:
	kfree(buf);
fail:
	return NULL;
}