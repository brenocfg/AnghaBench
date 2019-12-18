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
struct mem_ref {int /*<<< orphan*/ * vops; struct mem_ref* next; } ;
typedef  int /*<<< orphan*/  bitmap_head ;
typedef  int /*<<< orphan*/ * bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_and (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_default_obstack ; 
 int /*<<< orphan*/  bitmap_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_ior_into (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
find_more_ref_vops (struct mem_ref *mem_refs, bitmap clobbered_vops)
{
  bitmap_head tmp, all_vops;
  struct mem_ref *ref;

  bitmap_initialize (&tmp, &bitmap_default_obstack);
  bitmap_initialize (&all_vops, &bitmap_default_obstack);

  for (ref = mem_refs; ref; ref = ref->next)
    {
      /* The vops that are already in all_vops are accessed by more than
	 one memory reference.  */
      bitmap_and (&tmp, &all_vops, ref->vops);
      bitmap_ior_into (clobbered_vops, &tmp);
      bitmap_clear (&tmp);

      bitmap_ior_into (&all_vops, ref->vops);
    }

  bitmap_clear (&all_vops);
}