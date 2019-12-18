#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* debug_type ;
typedef  int /*<<< orphan*/  debug_field ;
struct TYPE_8__ {TYPE_1__* kclass; } ;
struct TYPE_9__ {int kind; TYPE_2__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  const* fields; } ;

/* Variables and functions */
#define  DEBUG_KIND_CLASS 131 
#define  DEBUG_KIND_STRUCT 130 
#define  DEBUG_KIND_UNION 129 
#define  DEBUG_KIND_UNION_CLASS 128 
 TYPE_3__* debug_get_real_type (void*,TYPE_3__*,int /*<<< orphan*/ *) ; 

const debug_field *
debug_get_fields (void *handle, debug_type type)
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
    case DEBUG_KIND_STRUCT:
    case DEBUG_KIND_UNION:
    case DEBUG_KIND_CLASS:
    case DEBUG_KIND_UNION_CLASS:
      return type->u.kclass->fields;
    }
  /*NOTREACHED*/
}