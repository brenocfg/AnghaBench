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
struct debug_buffer {char* output_buf; int (* fill_func ) (struct debug_buffer*) ;int count; int /*<<< orphan*/  alloc_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int stub1 (struct debug_buffer*) ; 
 scalar_t__ vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_buffer(struct debug_buffer *buf)
{
	int ret = 0;

	if (!buf->output_buf)
		buf->output_buf = (char *)vmalloc(buf->alloc_size);

	if (!buf->output_buf) {
		ret = -ENOMEM;
		goto out;
	}

	ret = buf->fill_func(buf);

	if (ret >= 0) {
		buf->count = ret;
		ret = 0;
	}

out:
	return ret;
}