#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* debug_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_10__ {TYPE_1__* kmethod; TYPE_3__* kfunction; } ;
struct TYPE_12__ {int kind; TYPE_2__ u; } ;
struct TYPE_11__ {TYPE_4__* const* arg_types; int /*<<< orphan*/  varargs; } ;
struct TYPE_9__ {TYPE_4__* const* arg_types; int /*<<< orphan*/  varargs; } ;

/* Variables and functions */
#define  DEBUG_KIND_FUNCTION 129 
#define  DEBUG_KIND_METHOD 128 
 TYPE_4__* debug_get_real_type (void*,TYPE_4__*,int /*<<< orphan*/ *) ; 

const debug_type *
debug_get_parameter_types (void *handle, debug_type type,
			   bfd_boolean *pvarargs)
{
  if (type == NULL)
    return NULL;

  type = debug_get_real_type (handle, type, NULL);
  if (type == NULL)
    return NULL;

  switch (type->kind)
    {
    default:
      return NULL;
    case DEBUG_KIND_FUNCTION:
      *pvarargs = type->u.kfunction->varargs;
      return type->u.kfunction->arg_types;
    case DEBUG_KIND_METHOD:
      *pvarargs = type->u.kmethod->varargs;
      return type->u.kmethod->arg_types;
    }
  /*NOTREACHED*/
}