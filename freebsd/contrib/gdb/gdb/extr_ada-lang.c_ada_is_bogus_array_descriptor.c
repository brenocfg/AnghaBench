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
 int /*<<< orphan*/  ada_is_array_descriptor (struct type*) ; 
 int /*<<< orphan*/ * lookup_struct_elt_type (struct type*,char*,int) ; 

int
ada_is_bogus_array_descriptor (struct type *type)
{
  return
    type != NULL
    && TYPE_CODE (type) == TYPE_CODE_STRUCT
    && (lookup_struct_elt_type (type, "P_BOUNDS", 1) != NULL
	|| lookup_struct_elt_type (type, "P_ARRAY", 1) != NULL)
    && !ada_is_array_descriptor (type);
}