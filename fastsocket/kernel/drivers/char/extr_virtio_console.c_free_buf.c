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
struct port_buffer {unsigned int sgpages; int /*<<< orphan*/ * sg; struct port_buffer* buf; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct port_buffer*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* sg_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_buf(struct port_buffer *buf)
{
	unsigned int i;

	kfree(buf->buf);
	for (i = 0; i < buf->sgpages; i++) {
		struct page *page = sg_page(&buf->sg[i]);
		if (!page)
			break;
		put_page(page);
	}

	kfree(buf);
}