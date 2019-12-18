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
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 struct type* ada_find_parallel_type (struct type*,char*) ; 
 struct type* dynamic_template_type (struct type*) ; 
 struct type* template_to_static_fixed_type (struct type*) ; 

__attribute__((used)) static struct type *
to_static_fixed_type (struct type *type0)
{
  struct type *type;

  if (type0 == NULL)
    return NULL;

  /* FIXME:  TYPE_FLAG_FIXED_INSTANCE should be defined in gdbtypes.h */
  /*  if (TYPE_FLAGS (type0) & TYPE_FLAG_FIXED_INSTANCE)
     return type0;
   */
  CHECK_TYPEDEF (type0);

  switch (TYPE_CODE (type0))
    {
    default:
      return type0;
    case TYPE_CODE_STRUCT:
      type = dynamic_template_type (type0);
      if (type != NULL)
	return template_to_static_fixed_type (type);
      return type0;
    case TYPE_CODE_UNION:
      type = ada_find_parallel_type (type0, "___XVU");
      if (type != NULL)
	return template_to_static_fixed_type (type);
      return type0;
    }
}