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
 scalar_t__ TYPE_CODE_CLASS ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_VIRTUAL (struct type*,int) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 scalar_t__ has_vtable (struct type*) ; 

struct type *
primary_base_class (struct type *dclass)
{
  /* In HP ANSI C++'s runtime model, a "primary base class" of a class
     is the first directly inherited, non-virtual base class that
     requires a virtual table */

  int i;

  if (TYPE_CODE (dclass) != TYPE_CODE_CLASS)
    return NULL;

  for (i = 0; i < TYPE_N_BASECLASSES (dclass); i++)
    if (!TYPE_FIELD_VIRTUAL (dclass, i) &&
	has_vtable (TYPE_FIELD_TYPE (dclass, i)))
      return TYPE_FIELD_TYPE (dclass, i);

  return NULL;
}