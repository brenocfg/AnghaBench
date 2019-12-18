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
struct circ_buf {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TI_WRITE_BUF_SIZE ; 
 int /*<<< orphan*/  kfree (struct circ_buf*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_buf_clear (struct circ_buf*) ; 

__attribute__((used)) static struct circ_buf *ti_buf_alloc(void)
{
	struct circ_buf *cb;

	cb = kmalloc(sizeof(struct circ_buf), GFP_KERNEL);
	if (cb == NULL)
		return NULL;

	cb->buf = kmalloc(TI_WRITE_BUF_SIZE, GFP_KERNEL);
	if (cb->buf == NULL) {
		kfree(cb);
		return NULL;
	}

	ti_buf_clear(cb);

	return cb;
}