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
 scalar_t__ TYPE_CODE_VOID ; 
 scalar_t__ ada_is_array_descriptor (struct type*) ; 
 scalar_t__ ada_is_packed_array_type (struct type*) ; 
 int /*<<< orphan*/ * ada_renaming_type (struct type*) ; 

int
ada_prefer_type (struct type *type0, struct type *type1)
{
  if (type1 == NULL)
    return 1;
  else if (type0 == NULL)
    return 0;
  else if (TYPE_CODE (type1) == TYPE_CODE_VOID)
    return 1;
  else if (TYPE_CODE (type0) == TYPE_CODE_VOID)
    return 0;
  else if (ada_is_packed_array_type (type0))
    return 1;
  else if (ada_is_array_descriptor (type0)
	   && !ada_is_array_descriptor (type1))
    return 1;
  else if (ada_renaming_type (type0) != NULL
	   && ada_renaming_type (type1) == NULL)
    return 1;
  return 0;
}