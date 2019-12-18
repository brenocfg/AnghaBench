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
struct objfile {int /*<<< orphan*/  objfile_obstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_FIELD_PHYSNAME (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 int /*<<< orphan*/ * TYPE_FIELDS (struct type*) ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_STATIC (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_STATIC_PHYSNAME (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  obstack_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strcat (scalar_t__,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
fix_static_member_physnames (struct type *type, char *class_name,
			     struct objfile *objfile)
{
  int i;

  /* We fix the member names only for classes or structs */
  if (TYPE_CODE (type) != TYPE_CODE_STRUCT)
    return;

  for (i = 0; i < TYPE_NFIELDS (type); i++)
    if (TYPE_FIELD_STATIC (type, i))
      {
	if (TYPE_FIELD_STATIC_PHYSNAME (type, i))
	  return;		/* physnames are already set */

	SET_FIELD_PHYSNAME (TYPE_FIELDS (type)[i],
			    obstack_alloc (&objfile->objfile_obstack,
	     strlen (class_name) + strlen (TYPE_FIELD_NAME (type, i)) + 3));
	strcpy (TYPE_FIELD_STATIC_PHYSNAME (type, i), class_name);
	strcat (TYPE_FIELD_STATIC_PHYSNAME (type, i), "::");
	strcat (TYPE_FIELD_STATIC_PHYSNAME (type, i), TYPE_FIELD_NAME (type, i));
      }
}