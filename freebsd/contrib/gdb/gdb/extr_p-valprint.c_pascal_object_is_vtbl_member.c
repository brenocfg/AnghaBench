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
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int pascal_object_is_vtbl_ptr_type (struct type*) ; 

int
pascal_object_is_vtbl_member (struct type *type)
{
  if (TYPE_CODE (type) == TYPE_CODE_PTR)
    {
      type = TYPE_TARGET_TYPE (type);
      if (TYPE_CODE (type) == TYPE_CODE_ARRAY)
	{
	  type = TYPE_TARGET_TYPE (type);
	  if (TYPE_CODE (type) == TYPE_CODE_STRUCT	/* if not using thunks */
	      || TYPE_CODE (type) == TYPE_CODE_PTR)	/* if using thunks */
	    {
	      /* Virtual functions tables are full of pointers
	         to virtual functions. */
	      return pascal_object_is_vtbl_ptr_type (type);
	    }
	}
    }
  return 0;
}