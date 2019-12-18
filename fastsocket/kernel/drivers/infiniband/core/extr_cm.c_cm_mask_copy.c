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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int IB_CM_COMPARE_SIZE ; 

__attribute__((used)) static void cm_mask_copy(u8 *dst, u8 *src, u8 *mask)
{
	int i;

	for (i = 0; i < IB_CM_COMPARE_SIZE / sizeof(unsigned long); i++)
		((unsigned long *) dst)[i] = ((unsigned long *) src)[i] &
					     ((unsigned long *) mask)[i];
}