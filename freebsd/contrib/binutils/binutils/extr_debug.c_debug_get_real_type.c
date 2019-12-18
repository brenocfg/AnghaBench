#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct debug_type_real_list {struct debug_type* t; struct debug_type_real_list* next; } ;
struct TYPE_6__ {TYPE_2__* knamed; TYPE_1__* kindirect; } ;
struct debug_type {int kind; TYPE_3__ u; } ;
typedef  struct debug_type* debug_type ;
struct TYPE_5__ {struct debug_type* type; } ;
struct TYPE_4__ {struct debug_type** slot; } ;

/* Variables and functions */
#define  DEBUG_KIND_INDIRECT 130 
#define  DEBUG_KIND_NAMED 129 
#define  DEBUG_KIND_TAGGED 128 
 char* _ (char*) ; 
 char* debug_get_type_name (void*,struct debug_type*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct debug_type *
debug_get_real_type (void *handle, debug_type type,
		     struct debug_type_real_list *list)
{
  struct debug_type_real_list *l;
  struct debug_type_real_list rl;

  switch (type->kind)
    {
    default:
      return type;

    case DEBUG_KIND_INDIRECT:
    case DEBUG_KIND_NAMED:
    case DEBUG_KIND_TAGGED:
      break;
    }

  for (l = list; l != NULL; l = l->next)
    {
      if (l->t == type || l == l->next)
	{
	  fprintf (stderr,
		   _("debug_get_real_type: circular debug information for %s\n"),
		   debug_get_type_name (handle, type));
	  return NULL;
	}
    }

  rl.next = list;
  rl.t = type;

  switch (type->kind)
    {
      /* The default case is just here to avoid warnings.  */
    default:
    case DEBUG_KIND_INDIRECT:
      if (*type->u.kindirect->slot != NULL)
	return debug_get_real_type (handle, *type->u.kindirect->slot, &rl);
      return type;
    case DEBUG_KIND_NAMED:
    case DEBUG_KIND_TAGGED:
      return debug_get_real_type (handle, type->u.knamed->type, &rl);
    }
  /*NOTREACHED*/
}