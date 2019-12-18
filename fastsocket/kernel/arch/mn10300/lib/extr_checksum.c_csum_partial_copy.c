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
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int /*<<< orphan*/  copy_from_user (void*,void const*,int) ; 
 int /*<<< orphan*/  csum_partial (void*,int,int /*<<< orphan*/ ) ; 

__wsum csum_partial_copy(const void *src, void *dst, int len, __wsum sum)
{
	copy_from_user(dst, src, len);
	return csum_partial(dst, len, sum);
}