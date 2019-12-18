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
struct ip_vs_dest {int /*<<< orphan*/  activeconns; } ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int
ip_vs_sed_dest_overhead(struct ip_vs_dest *dest)
{
	/*
	 * We only use the active connection number in the cost
	 * calculation here.
	 */
	return atomic_read(&dest->activeconns) + 1;
}