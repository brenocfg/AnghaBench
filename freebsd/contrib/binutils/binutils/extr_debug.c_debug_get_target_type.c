#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* debug_type ;
struct TYPE_7__ {TYPE_2__* kvolatile; TYPE_2__* kconst; TYPE_2__* kreference; TYPE_2__* kpointer; } ;
struct TYPE_8__ {int kind; TYPE_1__ u; } ;

/* Variables and functions */
#define  DEBUG_KIND_CONST 131 
#define  DEBUG_KIND_POINTER 130 
#define  DEBUG_KIND_REFERENCE 129 
#define  DEBUG_KIND_VOLATILE 128 
 TYPE_2__* debug_get_real_type (void*,TYPE_2__*,int /*<<< orphan*/ *) ; 

debug_type
debug_get_target_type (void *handle, debug_type type)
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
    case DEBUG_KIND_POINTER:
      return type->u.kpointer;
    case DEBUG_KIND_REFERENCE:
      return type->u.kreference;
    case DEBUG_KIND_CONST:
      return type->u.kconst;
    case DEBUG_KIND_VOLATILE:
      return type->u.kvolatile;
    }
  /*NOTREACHED*/
}