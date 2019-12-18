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
struct rtentry {int dummy; } ;

/* Variables and functions */
 int RTD_DEBUG ; 
 struct rtentry* rte_alloc_debug () ; 
 int rte_debug ; 
 int /*<<< orphan*/  rte_zone ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rtentry *
rte_alloc(void)
{
	if (rte_debug & RTD_DEBUG)
		return (rte_alloc_debug());

	return ((struct rtentry *)zalloc(rte_zone));
}