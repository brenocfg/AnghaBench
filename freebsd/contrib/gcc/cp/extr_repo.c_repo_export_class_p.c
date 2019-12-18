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
 int /*<<< orphan*/  CLASSTYPE_VTABLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 int IDENTIFIER_REPO_CHOSEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_use_repository ; 

bool
repo_export_class_p (tree class_type)
{
  if (!flag_use_repository)
    return false;
  if (!CLASSTYPE_VTABLES (class_type))
    return false;
  /* If the virtual table has been assigned to this translation unit,
     export the class.  */
  return (IDENTIFIER_REPO_CHOSEN
	  (DECL_ASSEMBLER_NAME (CLASSTYPE_VTABLES (class_type))));
}