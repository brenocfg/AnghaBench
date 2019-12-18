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
 scalar_t__ TYPE_CODE_ENUM ; 
 scalar_t__ TYPE_CODE_RANGE ; 
 scalar_t__ TYPE_UNSIGNED (struct type*) ; 

int
ada_is_modular_type (struct type *type)
{
  /* FIXME: base_type should be declared in gdbtypes.h, implemented in
     valarith.c */
  struct type *subranged_type;	/* = base_type (type); */

  return (subranged_type != NULL && TYPE_CODE (type) == TYPE_CODE_RANGE
	  && TYPE_CODE (subranged_type) != TYPE_CODE_ENUM
	  && TYPE_UNSIGNED (subranged_type));
}