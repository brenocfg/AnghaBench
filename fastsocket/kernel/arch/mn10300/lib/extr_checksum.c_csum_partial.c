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
typedef  scalar_t__ __wsum ;

/* Variables and functions */
 scalar_t__ do_csum (void const*,int) ; 

__wsum csum_partial(const void *buff, int len, __wsum sum)
{
	__wsum result;

	result = do_csum(buff, len);
	result += sum;
	if (sum > result)
		result++;
	return result;
}