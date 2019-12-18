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
struct drm_buffer {int size; struct drm_buffer** data; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (struct drm_buffer*) ; 

void drm_buffer_free(struct drm_buffer *buf)
{

	if (buf != NULL) {

		int nr_pages = buf->size / PAGE_SIZE + 1;
		int idx;
		for (idx = 0; idx < nr_pages; ++idx)
			kfree(buf->data[idx]);

		kfree(buf);
	}
}