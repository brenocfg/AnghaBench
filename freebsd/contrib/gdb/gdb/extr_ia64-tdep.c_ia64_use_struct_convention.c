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
 int TYPE_LENGTH (struct type*) ; 
 struct type* is_float_or_hfa_type (struct type*) ; 

int
ia64_use_struct_convention (int gcc_p, struct type *type)
{
  struct type *float_elt_type;

  /* HFAs are structures (or arrays) consisting entirely of floating
     point values of the same length.  Up to 8 of these are returned
     in registers.  Don't use the struct convention when this is the
     case.  */
  float_elt_type = is_float_or_hfa_type (type);
  if (float_elt_type != NULL
      && TYPE_LENGTH (type) / TYPE_LENGTH (float_elt_type) <= 8)
    return 0;

  /* Other structs of length 32 or less are returned in r8-r11.
     Don't use the struct convention for those either.  */
  return TYPE_LENGTH (type) > 32;
}