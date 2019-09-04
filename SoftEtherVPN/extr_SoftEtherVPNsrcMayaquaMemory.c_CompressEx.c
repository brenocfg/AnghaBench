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
 scalar_t__ compress2 (void*,unsigned long*,void*,unsigned long,int) ; 

UINT CompressEx(void *dst, UINT dst_size, void *src, UINT src_size, UINT level)
{
	unsigned long dst_size_long = dst_size;
	// Validate arguments
	if (dst == NULL || dst_size_long == 0 || src == NULL)
	{
		return 0;
	}

	if (compress2(dst, &dst_size_long, src, src_size, (int)level) != Z_OK)
	{
		return 0;
	}

	return dst_size_long;
}