#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct debug_class_type* kclass; } ;
struct debug_type {scalar_t__ kind; TYPE_1__ u; } ;
struct debug_handle {scalar_t__ base_id; scalar_t__ class_id; struct debug_class_id* id_list; } ;
struct debug_class_type {scalar_t__ id; } ;
struct debug_class_id {char const* tag; struct debug_class_id* next; struct debug_type* type; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 scalar_t__ DEBUG_KIND_CLASS ; 
 scalar_t__ DEBUG_KIND_STRUCT ; 
 scalar_t__ DEBUG_KIND_UNION ; 
 scalar_t__ DEBUG_KIND_UNION_CLASS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ debug_type_samep (struct debug_handle*,struct debug_type*,struct debug_type*) ; 
 int /*<<< orphan*/  memset (struct debug_class_id*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
debug_set_class_id (struct debug_handle *info, const char *tag,
		    struct debug_type *type)
{
  struct debug_class_type *c;
  struct debug_class_id *l;

  assert (type->kind == DEBUG_KIND_STRUCT
	  || type->kind == DEBUG_KIND_UNION
	  || type->kind == DEBUG_KIND_CLASS
	  || type->kind == DEBUG_KIND_UNION_CLASS);

  c = type->u.kclass;

  if (c->id > info->base_id)
    return TRUE;

  for (l = info->id_list; l != NULL; l = l->next)
    {
      if (l->type->kind != type->kind)
	continue;

      if (tag == NULL)
	{
	  if (l->tag != NULL)
	    continue;
	}
      else
	{
	  if (l->tag == NULL
	      || l->tag[0] != tag[0]
	      || strcmp (l->tag, tag) != 0)
	    continue;
	}

      if (debug_type_samep (info, l->type, type))
	{
	  c->id = l->type->u.kclass->id;
	  return TRUE;
	}
    }

  /* There are no identical types.  Use a new ID, and add it to the
     list.  */
  ++info->class_id;
  c->id = info->class_id;

  l = (struct debug_class_id *) xmalloc (sizeof *l);
  memset (l, 0, sizeof *l);

  l->type = type;
  l->tag = tag;

  l->next = info->id_list;
  info->id_list = l;

  return TRUE;
}