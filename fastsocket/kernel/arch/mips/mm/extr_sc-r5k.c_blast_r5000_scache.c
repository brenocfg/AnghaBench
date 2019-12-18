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
 unsigned long INDEX_BASE ; 
 int /*<<< orphan*/  R5K_Page_Invalidate_S ; 
 scalar_t__ SC_PAGE ; 
 int /*<<< orphan*/  cache_op (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long scache_size ; 

__attribute__((used)) static inline void blast_r5000_scache(void)
{
	unsigned long start = INDEX_BASE;
	unsigned long end = start + scache_size;

	while(start < end) {
		cache_op(R5K_Page_Invalidate_S, start);
		start += SC_PAGE;
	}
}