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
 scalar_t__ TYPE_CODE_VOID ; 

__attribute__((used)) static int
return_match (struct type *func_type, struct type *context_type)
{
  struct type *return_type;

  if (func_type == NULL)
    return 1;

  /* FIXME: base_type should be declared in gdbtypes.h, implemented in valarith.c */
  /*  if (TYPE_CODE (func_type) == TYPE_CODE_FUNC)
     return_type = base_type (TYPE_TARGET_TYPE (func_type));
     else 
     return_type = base_type (func_type); */
  if (return_type == NULL)
    return 1;

  /* FIXME: base_type should be declared in gdbtypes.h, implemented in valarith.c */
  /*  context_type = base_type (context_type); */

  if (TYPE_CODE (return_type) == TYPE_CODE_ENUM)
    return context_type == NULL || return_type == context_type;
  else if (context_type == NULL)
    return TYPE_CODE (return_type) != TYPE_CODE_VOID;
  else
    return TYPE_CODE (return_type) == TYPE_CODE (context_type);
}