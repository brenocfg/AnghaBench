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
struct mem_ref {struct mem_ref* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_mem_ref (struct mem_ref*) ; 

__attribute__((used)) static void
free_mem_refs (struct mem_ref *refs)
{
  struct mem_ref *ref, *next;

  for (ref = refs; ref; ref = next)
    {
      next = ref->next;
      free_mem_ref (ref);
    }
}