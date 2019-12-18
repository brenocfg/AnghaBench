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
struct cache_head {int dummy; } ;
struct cache_detail {int (* cache_upcall ) (struct cache_detail*,struct cache_head*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct cache_detail*,struct cache_head*) ; 

__attribute__((used)) static int cache_make_upcall(struct cache_detail *cd, struct cache_head *h)
{
	if (!cd->cache_upcall)
		return -EINVAL;
	return cd->cache_upcall(cd, h);
}