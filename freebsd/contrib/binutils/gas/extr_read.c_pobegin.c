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

/* Variables and functions */
 int /*<<< orphan*/  cfi_pop_insert () ; 
 int /*<<< orphan*/  hash_new () ; 
 int /*<<< orphan*/  md_pop_insert () ; 
 int /*<<< orphan*/  obj_pop_insert () ; 
 int /*<<< orphan*/  po_hash ; 
 int /*<<< orphan*/  pop_insert (int /*<<< orphan*/ ) ; 
 int pop_override_ok ; 
 char* pop_table_name ; 
 int /*<<< orphan*/  potable ; 

__attribute__((used)) static void
pobegin (void)
{
  po_hash = hash_new ();

  /* Do the target-specific pseudo ops.  */
  pop_table_name = "md";
  md_pop_insert ();

  /* Now object specific.  Skip any that were in the target table.  */
  pop_table_name = "obj";
  pop_override_ok = 1;
  obj_pop_insert ();

  /* Now portable ones.  Skip any that we've seen already.  */
  pop_table_name = "standard";
  pop_insert (potable);

#ifdef TARGET_USE_CFIPOP
  pop_table_name = "cfi";
  pop_override_ok = 1;
  cfi_pop_insert ();
#endif
}