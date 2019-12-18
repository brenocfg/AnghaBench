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
 int /*<<< orphan*/  DRM_ERROR (char*,int,int,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (struct drm_buffer*) ; 
 struct drm_buffer* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 

int drm_buffer_alloc(struct drm_buffer **buf, int size)
{
	int nr_pages = size / PAGE_SIZE + 1;
	int idx;

	/* Allocating pointer table to end of structure makes drm_buffer
	 * variable sized */
	*buf = kzalloc(sizeof(struct drm_buffer) + nr_pages*sizeof(char *),
			GFP_KERNEL);

	if (*buf == NULL) {
		DRM_ERROR("Failed to allocate drm buffer object to hold"
				" %d bytes in %d pages.\n",
				size, nr_pages);
		return -ENOMEM;
	}

	(*buf)->size = size;

	for (idx = 0; idx < nr_pages; ++idx) {

		(*buf)->data[idx] =
			kmalloc(min(PAGE_SIZE, size - idx * PAGE_SIZE),
				GFP_KERNEL);


		if ((*buf)->data[idx] == NULL) {
			DRM_ERROR("Failed to allocate %dth page for drm"
					" buffer with %d bytes and %d pages.\n",
					idx + 1, size, nr_pages);
			goto error_out;
		}

	}

	return 0;

error_out:

	/* Only last element can be null pointer so check for it first. */
	if ((*buf)->data[idx])
		kfree((*buf)->data[idx]);

	for (--idx; idx >= 0; --idx)
		kfree((*buf)->data[idx]);

	kfree(*buf);
	return -ENOMEM;
}