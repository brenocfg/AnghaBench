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
 scalar_t__ TYPE_CODE_STRUCT ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 struct type* check_typedef (struct type*) ; 
 struct type* desc_base_type (struct type*) ; 
 scalar_t__ is_thin_pntr (struct type*) ; 
 struct type* lookup_struct_elt_type (struct type*,char*,int) ; 
 struct type* thin_descriptor_type (struct type*) ; 

__attribute__((used)) static struct type *
desc_bounds_type (struct type *type)
{
  struct type *r;

  type = desc_base_type (type);

  if (type == NULL)
    return NULL;
  else if (is_thin_pntr (type))
    {
      type = thin_descriptor_type (type);
      if (type == NULL)
	return NULL;
      r = lookup_struct_elt_type (type, "BOUNDS", 1);
      if (r != NULL)
	return check_typedef (r);
    }
  else if (TYPE_CODE (type) == TYPE_CODE_STRUCT)
    {
      r = lookup_struct_elt_type (type, "P_BOUNDS", 1);
      if (r != NULL)
	return check_typedef (TYPE_TARGET_TYPE (check_typedef (r)));
    }
  return NULL;
}