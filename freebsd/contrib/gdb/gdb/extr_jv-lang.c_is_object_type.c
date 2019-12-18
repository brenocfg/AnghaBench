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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 struct type* TYPE_BASECLASS (struct type*,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 char* TYPE_FIELD_NAME (struct type*,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_NFIELDS (struct type*) ; 
 scalar_t__ TYPE_N_BASECLASSES (struct type*) ; 
 char* TYPE_TAG_NAME (struct type*) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (struct type*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 struct type* java_object_type ; 
 scalar_t__ strcmp (char*,char*) ; 

int
is_object_type (struct type *type)
{
  CHECK_TYPEDEF (type);
  if (TYPE_CODE (type) == TYPE_CODE_PTR)
    {
      struct type *ttype = check_typedef (TYPE_TARGET_TYPE (type));
      char *name;
      if (TYPE_CODE (ttype) != TYPE_CODE_STRUCT)
	return 0;
      while (TYPE_N_BASECLASSES (ttype) > 0)
	ttype = TYPE_BASECLASS (ttype, 0);
      name = TYPE_TAG_NAME (ttype);
      if (name != NULL && strcmp (name, "java.lang.Object") == 0)
	return 1;
      name = TYPE_NFIELDS (ttype) > 0 ? TYPE_FIELD_NAME (ttype, 0) : (char *) 0;
      if (name != NULL && strcmp (name, "vtable") == 0)
	{
	  if (java_object_type == NULL)
	    java_object_type = type;
	  return 1;
	}
    }
  return 0;
}