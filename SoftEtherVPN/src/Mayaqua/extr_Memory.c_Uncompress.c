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
typedef  unsigned long UINT ;

/* Variables and functions */
 scalar_t__ Z_OK ; 
 scalar_t__ uncompress (void*,unsigned long*,void*,unsigned long) ; 

UINT Uncompress(void *dst, UINT dst_size, void *src, UINT src_size)
{
	unsigned long dst_size_long = dst_size;
	// Validate arguments
	if (dst == NULL || dst_size_long == 0 || src == NULL)
	{
		return 0;
	}

	if (uncompress(dst, &dst_size_long, src, src_size) != Z_OK)
	{
		return 0;
	}

	return (UINT)dst_size_long;
}