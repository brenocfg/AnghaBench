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
struct value {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 struct type* VALUE_TYPE (struct value*) ; 
 scalar_t__ is_thick_pntr (struct type*) ; 
 scalar_t__ is_thin_pntr (struct type*) ; 
 struct value* thin_data_pntr (struct value*) ; 
 struct value* value_struct_elt (struct value**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static struct value *
desc_data (struct value *arr)
{
  struct type *type = VALUE_TYPE (arr);
  if (is_thin_pntr (type))
    return thin_data_pntr (arr);
  else if (is_thick_pntr (type))
    return value_struct_elt (&arr, NULL, "P_ARRAY", NULL,
			     "Bad GNAT array descriptor");
  else
    return NULL;
}