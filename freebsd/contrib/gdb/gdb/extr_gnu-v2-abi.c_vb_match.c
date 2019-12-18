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
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int /*<<< orphan*/ * TYPE_NAME (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 scalar_t__ is_cplus_marker (char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vb_match (struct type *type, int index, struct type *basetype)
{
  struct type *fieldtype;
  char *name = TYPE_FIELD_NAME (type, index);
  char *field_class_name = NULL;

  if (*name != '_')
    return 0;
  /* gcc 2.4 uses _vb$.  */
  if (name[1] == 'v' && name[2] == 'b' && is_cplus_marker (name[3]))
    field_class_name = name + 4;
  /* gcc 2.5 will use __vb_.  */
  if (name[1] == '_' && name[2] == 'v' && name[3] == 'b' && name[4] == '_')
    field_class_name = name + 5;

  if (field_class_name == NULL)
    /* This field is not a virtual base class pointer.  */
    return 0;

  /* It's a virtual baseclass pointer, now we just need to find out whether
     it is for this baseclass.  */
  fieldtype = TYPE_FIELD_TYPE (type, index);
  if (fieldtype == NULL
      || TYPE_CODE (fieldtype) != TYPE_CODE_PTR)
    /* "Can't happen".  */
    return 0;

  /* What we check for is that either the types are equal (needed for
     nameless types) or have the same name.  This is ugly, and a more
     elegant solution should be devised (which would probably just push
     the ugliness into symbol reading unless we change the stabs format).  */
  if (TYPE_TARGET_TYPE (fieldtype) == basetype)
    return 1;

  if (TYPE_NAME (basetype) != NULL
      && TYPE_NAME (TYPE_TARGET_TYPE (fieldtype)) != NULL
      && strcmp (TYPE_NAME (basetype),
		 TYPE_NAME (TYPE_TARGET_TYPE (fieldtype))) == 0)
    return 1;
  return 0;
}