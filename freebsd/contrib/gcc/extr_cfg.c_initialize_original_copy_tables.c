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
struct htab_bb_copy_original_entry {int dummy; } ;

/* Variables and functions */
 void* bb_copy ; 
 int /*<<< orphan*/  bb_copy_original_eq ; 
 int /*<<< orphan*/  bb_copy_original_hash ; 
 void* bb_original ; 
 scalar_t__ create_alloc_pool (char*,int,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 void* htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ original_copy_bb_pool ; 

void
initialize_original_copy_tables (void)
{
  gcc_assert (!original_copy_bb_pool);
  original_copy_bb_pool
    = create_alloc_pool ("original_copy",
			 sizeof (struct htab_bb_copy_original_entry), 10);
  bb_original = htab_create (10, bb_copy_original_hash,
			     bb_copy_original_eq, NULL);
  bb_copy = htab_create (10, bb_copy_original_hash, bb_copy_original_eq, NULL);
}