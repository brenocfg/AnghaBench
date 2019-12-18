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
typedef  int u64 ;
struct xv_pool {int total_pages; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 

u64 xv_get_total_size_bytes(struct xv_pool *pool)
{
	return pool->total_pages << PAGE_SHIFT;
}