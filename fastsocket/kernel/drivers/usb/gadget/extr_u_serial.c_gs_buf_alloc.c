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
struct gs_buf {unsigned int buf_size; int /*<<< orphan*/ * buf_buf; int /*<<< orphan*/ * buf_get; int /*<<< orphan*/ * buf_put; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gs_buf_alloc(struct gs_buf *gb, unsigned size)
{
	gb->buf_buf = kmalloc(size, GFP_KERNEL);
	if (gb->buf_buf == NULL)
		return -ENOMEM;

	gb->buf_size = size;
	gb->buf_put = gb->buf_buf;
	gb->buf_get = gb->buf_buf;

	return 0;
}