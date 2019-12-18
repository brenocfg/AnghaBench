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
 struct type* desc_base_type (struct type*) ; 
 int /*<<< orphan*/ * lookup_struct_elt_type (struct type*,char*,int) ; 

__attribute__((used)) static int
is_thick_pntr (struct type *type)
{
  type = desc_base_type (type);
  return (type != NULL && TYPE_CODE (type) == TYPE_CODE_STRUCT
	  && lookup_struct_elt_type (type, "P_BOUNDS", 1) != NULL);
}