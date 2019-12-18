#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct shared_bitmap_info {int /*<<< orphan*/  hashcode; int /*<<< orphan*/ * pt_vars; } ;
typedef  TYPE_1__* shared_bitmap_info_t ;
typedef  int /*<<< orphan*/ * bitmap ;
struct TYPE_2__ {int /*<<< orphan*/ * pt_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_INSERT ; 
 int /*<<< orphan*/  bitmap_hash (int /*<<< orphan*/ *) ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,struct shared_bitmap_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shared_bitmap_table ; 

__attribute__((used)) static bitmap
shared_bitmap_lookup (bitmap pt_vars)
{
  void **slot;
  struct shared_bitmap_info sbi;

  sbi.pt_vars = pt_vars;
  sbi.hashcode = bitmap_hash (pt_vars);
  
  slot = htab_find_slot_with_hash (shared_bitmap_table, &sbi,
				   sbi.hashcode, NO_INSERT);
  if (!slot)
    return NULL;
  else
    return ((shared_bitmap_info_t) *slot)->pt_vars;
}