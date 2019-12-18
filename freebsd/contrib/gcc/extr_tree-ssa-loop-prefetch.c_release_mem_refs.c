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
struct mem_ref_group {struct mem_ref_group* next; struct mem_ref_group* refs; } ;
struct mem_ref {struct mem_ref* next; struct mem_ref* refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mem_ref_group*) ; 

__attribute__((used)) static void
release_mem_refs (struct mem_ref_group *groups)
{
  struct mem_ref_group *next_g;
  struct mem_ref *ref, *next_r;

  for (; groups; groups = next_g)
    {
      next_g = groups->next;
      for (ref = groups->refs; ref; ref = next_r)
	{
	  next_r = ref->next;
	  free (ref);
	}
      free (groups);
    }
}