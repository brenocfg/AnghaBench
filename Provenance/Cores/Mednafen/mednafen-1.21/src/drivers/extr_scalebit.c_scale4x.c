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

/* Variables and functions */
 void* alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  scale4x_buf (void*,unsigned int,void*,unsigned int,void const*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void scale4x(void* void_dst, unsigned dst_slice, const void* void_src, unsigned src_slice, unsigned pixel, unsigned width, unsigned height)
{
	unsigned mid_slice;
	void* mid;

	mid_slice = 2 * pixel * width; /* required space for 1 row buffer */

	mid_slice = (mid_slice + 0x7) & ~0x7; /* align to 8 bytes */

#if HAVE_ALLOCA
	mid = alloca(6 * mid_slice); /* allocate space for 6 row buffers */

	assert(mid != 0); /* alloca should never fails */
#else
	mid = malloc(6 * mid_slice); /* allocate space for 6 row buffers */

	if (!mid)
		return;
#endif

	scale4x_buf(void_dst, dst_slice, mid, mid_slice, void_src, src_slice, pixel, width, height);

#if !HAVE_ALLOCA
	free(mid);
#endif
}