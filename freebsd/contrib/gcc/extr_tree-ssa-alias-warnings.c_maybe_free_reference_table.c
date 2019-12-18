#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  objs; int /*<<< orphan*/  ptrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_alloc_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 TYPE_1__* ref_table ; 
 int /*<<< orphan*/ * ref_table_alloc_pool ; 

__attribute__((used)) static void
maybe_free_reference_table (void)
{
  if (ref_table)
    {
      htab_delete (ref_table->ptrs);
      htab_delete (ref_table->objs);
      free (ref_table);
      ref_table = NULL;
    }

  if (ref_table_alloc_pool)
    {
      free_alloc_pool (ref_table_alloc_pool);
      ref_table_alloc_pool = NULL;
    }
}