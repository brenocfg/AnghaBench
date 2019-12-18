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
struct pl2303_buf {unsigned int buf_size; int /*<<< orphan*/ * buf_buf; int /*<<< orphan*/ * buf_put; int /*<<< orphan*/ * buf_get; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct pl2303_buf*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pl2303_buf *pl2303_buf_alloc(unsigned int size)
{
	struct pl2303_buf *pb;

	if (size == 0)
		return NULL;

	pb = kmalloc(sizeof(struct pl2303_buf), GFP_KERNEL);
	if (pb == NULL)
		return NULL;

	pb->buf_buf = kmalloc(size, GFP_KERNEL);
	if (pb->buf_buf == NULL) {
		kfree(pb);
		return NULL;
	}

	pb->buf_size = size;
	pb->buf_get = pb->buf_put = pb->buf_buf;

	return pb;
}