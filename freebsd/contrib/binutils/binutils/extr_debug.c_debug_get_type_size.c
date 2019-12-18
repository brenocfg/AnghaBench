#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* debug_type ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_7__ {TYPE_3__* knamed; TYPE_1__* kindirect; } ;
struct TYPE_9__ {scalar_t__ size; int kind; TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_4__* type; } ;
struct TYPE_6__ {TYPE_4__** slot; } ;

/* Variables and functions */
#define  DEBUG_KIND_INDIRECT 130 
#define  DEBUG_KIND_NAMED 129 
#define  DEBUG_KIND_TAGGED 128 

bfd_vma
debug_get_type_size (void *handle, debug_type type)
{
  if (type == NULL)
    return 0;

  /* We don't call debug_get_real_type, because somebody might have
     called debug_record_type_size on a named or indirect type.  */

  if (type->size != 0)
    return type->size;

  switch (type->kind)
    {
    default:
      return 0;
    case DEBUG_KIND_INDIRECT:
      if (*type->u.kindirect->slot != NULL)
	return debug_get_type_size (handle, *type->u.kindirect->slot);
      return 0;
    case DEBUG_KIND_NAMED:
    case DEBUG_KIND_TAGGED:
      return debug_get_type_size (handle, type->u.knamed->type);
    }
  /*NOTREACHED*/
}