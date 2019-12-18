#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* debug_type ;
struct TYPE_12__ {TYPE_2__* kmethod; TYPE_1__* kfunction; } ;
struct TYPE_13__ {int kind; TYPE_3__ u; } ;
struct TYPE_11__ {TYPE_4__* return_type; } ;
struct TYPE_10__ {TYPE_4__* return_type; } ;

/* Variables and functions */
#define  DEBUG_KIND_FUNCTION 129 
#define  DEBUG_KIND_METHOD 128 
 TYPE_4__* DEBUG_TYPE_NULL ; 
 TYPE_4__* debug_get_real_type (void*,TYPE_4__*,int /*<<< orphan*/ *) ; 

debug_type
debug_get_return_type (void *handle, debug_type type)
{
  if (type == NULL)
    return DEBUG_TYPE_NULL;

  type = debug_get_real_type (handle, type, NULL);
  if (type == NULL)
    return DEBUG_TYPE_NULL;

  switch (type->kind)
    {
    default:
      return DEBUG_TYPE_NULL;
    case DEBUG_KIND_FUNCTION:
      return type->u.kfunction->return_type;
    case DEBUG_KIND_METHOD:
      return type->u.kmethod->return_type;
    }
  /*NOTREACHED*/
}