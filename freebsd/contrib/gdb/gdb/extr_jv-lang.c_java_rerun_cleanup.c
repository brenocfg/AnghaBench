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
 int /*<<< orphan*/ * class_symtab ; 
 int /*<<< orphan*/ * dynamics_objfile ; 
 int /*<<< orphan*/  free_objfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_symtab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * java_object_type ; 

void
java_rerun_cleanup (void)
{
  if (class_symtab != NULL)
    {
      free_symtab (class_symtab);	/* ??? */
      class_symtab = NULL;
    }
  if (dynamics_objfile != NULL)
    {
      free_objfile (dynamics_objfile);
      dynamics_objfile = NULL;
    }

  java_object_type = NULL;
}