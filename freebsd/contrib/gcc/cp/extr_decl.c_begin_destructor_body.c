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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_class_ptr ; 
 int /*<<< orphan*/  current_class_type ; 
 int /*<<< orphan*/  finish_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_vtbl_ptrs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_base_cleanups () ; 

__attribute__((used)) static void
begin_destructor_body (void)
{
  tree compound_stmt;

  /* If the CURRENT_CLASS_TYPE is incomplete, we will have already
     issued an error message.  We still want to try to process the
     body of the function, but initialize_vtbl_ptrs will crash if
     TYPE_BINFO is NULL.  */
  if (COMPLETE_TYPE_P (current_class_type))
    {
      compound_stmt = begin_compound_stmt (0);
      /* Make all virtual function table pointers in non-virtual base
	 classes point to CURRENT_CLASS_TYPE's virtual function
	 tables.  */
      initialize_vtbl_ptrs (current_class_ptr);
      finish_compound_stmt (compound_stmt);

      /* And insert cleanups for our bases and members so that they
	 will be properly destroyed if we throw.  */
      push_base_cleanups ();
    }
}