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
 scalar_t__ B_TST (scalar_t__,int) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_CLASS ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_VIRTUAL_BITS (struct type*) ; 
 int /*<<< orphan*/  TYPE_FN_FIELDLIST1 (struct type*,int) ; 
 scalar_t__ TYPE_FN_FIELDLISTS (struct type*) ; 
 scalar_t__ TYPE_FN_FIELD_VIRTUAL_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TYPE_NFN_FIELDS (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 

int
has_vtable (struct type *dclass)
{
  /* In the HP ANSI C++ runtime model, a class has a vtable only if it
     has virtual functions or virtual bases.  */

  int i;

  if (TYPE_CODE (dclass) != TYPE_CODE_CLASS)
    return 0;

  /* First check for the presence of virtual bases */
  if (TYPE_FIELD_VIRTUAL_BITS (dclass))
    for (i = 0; i < TYPE_N_BASECLASSES (dclass); i++)
      if (B_TST (TYPE_FIELD_VIRTUAL_BITS (dclass), i))
	return 1;

  /* Next check for virtual functions */
  if (TYPE_FN_FIELDLISTS (dclass))
    for (i = 0; i < TYPE_NFN_FIELDS (dclass); i++)
      if (TYPE_FN_FIELD_VIRTUAL_P (TYPE_FN_FIELDLIST1 (dclass, i), 0))
	return 1;

  /* Recurse on non-virtual bases to see if any of them needs a vtable */
  if (TYPE_FIELD_VIRTUAL_BITS (dclass))
    for (i = 0; i < TYPE_N_BASECLASSES (dclass); i++)
      if ((!B_TST (TYPE_FIELD_VIRTUAL_BITS (dclass), i)) &&
	  (has_vtable (TYPE_FIELD_TYPE (dclass, i))))
	return 1;

  /* Well, maybe we don't need a virtual table */
  return 0;
}