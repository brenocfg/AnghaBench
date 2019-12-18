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
typedef  int uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int TTM_PL_PRIV5 ; 

__attribute__((used)) static inline int ttm_mem_type_from_flags(uint32_t flags, uint32_t *mem_type)
{
	int i;

	for (i = 0; i <= TTM_PL_PRIV5; i++)
		if (flags & (1 << i)) {
			*mem_type = i;
			return 0;
		}
	return -EINVAL;
}