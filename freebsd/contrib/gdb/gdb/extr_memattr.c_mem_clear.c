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
struct mem_region {struct mem_region* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_mem_region (struct mem_region*) ; 
 struct mem_region* mem_region_chain ; 

__attribute__((used)) static void
mem_clear (void)
{
  struct mem_region *m;

  while ((m = mem_region_chain) != 0)
    {
      mem_region_chain = m->next;
      delete_mem_region (m);
    }
}