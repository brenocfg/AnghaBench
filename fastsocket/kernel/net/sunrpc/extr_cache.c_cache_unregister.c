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
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_unregister_net (struct cache_detail*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 

void cache_unregister(struct cache_detail *cd)
{
	cache_unregister_net(cd, &init_net);
}