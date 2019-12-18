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
struct lguest_pages {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int SHARED_SWITCHER_PAGES ; 
 scalar_t__ SWITCHER_ADDR ; 

__attribute__((used)) static struct lguest_pages *lguest_pages(unsigned int cpu)
{
	return &(((struct lguest_pages *)
		  (SWITCHER_ADDR + SHARED_SWITCHER_PAGES*PAGE_SIZE))[cpu]);
}