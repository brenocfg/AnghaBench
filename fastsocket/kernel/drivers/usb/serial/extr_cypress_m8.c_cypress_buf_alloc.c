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
struct cypress_buf {unsigned int buf_size; int /*<<< orphan*/ * buf_buf; int /*<<< orphan*/ * buf_put; int /*<<< orphan*/ * buf_get; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct cypress_buf*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cypress_buf *cypress_buf_alloc(unsigned int size)
{

	struct cypress_buf *cb;


	if (size == 0)
		return NULL;

	cb = kmalloc(sizeof(struct cypress_buf), GFP_KERNEL);
	if (cb == NULL)
		return NULL;

	cb->buf_buf = kmalloc(size, GFP_KERNEL);
	if (cb->buf_buf == NULL) {
		kfree(cb);
		return NULL;
	}

	cb->buf_size = size;
	cb->buf_get = cb->buf_put = cb->buf_buf;

	return cb;

}