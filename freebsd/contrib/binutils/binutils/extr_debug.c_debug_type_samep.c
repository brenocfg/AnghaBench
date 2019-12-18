#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct debug_type_compare_list {struct debug_type_compare_list* next; struct debug_type* t2; struct debug_type* t1; } ;
struct TYPE_15__ {TYPE_11__* knamed; struct debug_type* kvolatile; struct debug_type* kconst; TYPE_9__* kmethod; TYPE_8__* koffset; TYPE_7__* kset; TYPE_6__* karray; TYPE_5__* krange; struct debug_type* kreference; TYPE_4__* kfunction; struct debug_type* kpointer; TYPE_3__* kenum; TYPE_2__* kclass; int /*<<< orphan*/  kint; TYPE_1__* kindirect; } ;
struct debug_type {scalar_t__ kind; scalar_t__ size; TYPE_12__ u; } ;
struct debug_handle {struct debug_type_compare_list* compare_list; int /*<<< orphan*/  base_id; } ;
typedef  int /*<<< orphan*/  bfd_signed_vma ;
typedef  int bfd_boolean ;
struct TYPE_24__ {struct debug_type** arg_types; struct debug_type* domain_type; struct debug_type* return_type; int /*<<< orphan*/  varargs; } ;
struct TYPE_23__ {struct debug_type* target_type; struct debug_type* base_type; } ;
struct TYPE_22__ {struct debug_type* type; int /*<<< orphan*/  bitstringp; } ;
struct TYPE_21__ {struct debug_type* element_type; int /*<<< orphan*/  stringp; int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_20__ {struct debug_type* type; int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_19__ {struct debug_type** arg_types; struct debug_type* return_type; int /*<<< orphan*/  varargs; } ;
struct TYPE_18__ {char** names; int /*<<< orphan*/ * values; } ;
struct TYPE_17__ {int /*<<< orphan*/  id; } ;
struct TYPE_16__ {struct debug_type** slot; } ;
struct TYPE_14__ {struct debug_type* type; TYPE_10__* name; } ;
struct TYPE_13__ {char const* name; } ;

/* Variables and functions */
#define  DEBUG_KIND_ARRAY 149 
#define  DEBUG_KIND_BOOL 148 
#define  DEBUG_KIND_CLASS 147 
#define  DEBUG_KIND_COMPLEX 146 
#define  DEBUG_KIND_CONST 145 
#define  DEBUG_KIND_ENUM 144 
#define  DEBUG_KIND_FLOAT 143 
#define  DEBUG_KIND_FUNCTION 142 
 scalar_t__ DEBUG_KIND_INDIRECT ; 
#define  DEBUG_KIND_INT 141 
#define  DEBUG_KIND_METHOD 140 
#define  DEBUG_KIND_NAMED 139 
#define  DEBUG_KIND_OFFSET 138 
#define  DEBUG_KIND_POINTER 137 
#define  DEBUG_KIND_RANGE 136 
#define  DEBUG_KIND_REFERENCE 135 
#define  DEBUG_KIND_SET 134 
#define  DEBUG_KIND_STRUCT 133 
#define  DEBUG_KIND_TAGGED 132 
#define  DEBUG_KIND_UNION 131 
#define  DEBUG_KIND_UNION_CLASS 130 
#define  DEBUG_KIND_VOID 129 
#define  DEBUG_KIND_VOLATILE 128 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int debug_class_type_samep (struct debug_handle*,struct debug_type*,struct debug_type*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static bfd_boolean
debug_type_samep (struct debug_handle *info, struct debug_type *t1,
		  struct debug_type *t2)
{
  struct debug_type_compare_list *l;
  struct debug_type_compare_list top;
  bfd_boolean ret;

  if (t1 == NULL)
    return t2 == NULL;
  if (t2 == NULL)
    return FALSE;

  while (t1->kind == DEBUG_KIND_INDIRECT)
    {
      t1 = *t1->u.kindirect->slot;
      if (t1 == NULL)
	return FALSE;
    }
  while (t2->kind == DEBUG_KIND_INDIRECT)
    {
      t2 = *t2->u.kindirect->slot;
      if (t2 == NULL)
	return FALSE;
    }

  if (t1 == t2)
    return TRUE;

  /* As a special case, permit a typedef to match a tag, since C++
     debugging output will sometimes add a typedef where C debugging
     output will not.  */
  if (t1->kind == DEBUG_KIND_NAMED
      && t2->kind == DEBUG_KIND_TAGGED)
    return debug_type_samep (info, t1->u.knamed->type, t2);
  else if (t1->kind == DEBUG_KIND_TAGGED
	   && t2->kind == DEBUG_KIND_NAMED)
    return debug_type_samep (info, t1, t2->u.knamed->type);

  if (t1->kind != t2->kind
      || t1->size != t2->size)
    return FALSE;

  /* Get rid of the trivial cases first.  */
  switch (t1->kind)
    {
    default:
      break;
    case DEBUG_KIND_VOID:
    case DEBUG_KIND_FLOAT:
    case DEBUG_KIND_COMPLEX:
    case DEBUG_KIND_BOOL:
      return TRUE;
    case DEBUG_KIND_INT:
      return t1->u.kint == t2->u.kint;
    }

  /* We have to avoid an infinite recursion.  We do this by keeping a
     list of types which we are comparing.  We just keep the list on
     the stack.  If we encounter a pair of types we are currently
     comparing, we just assume that they are equal.  */
  for (l = info->compare_list; l != NULL; l = l->next)
    {
      if (l->t1 == t1 && l->t2 == t2)
	return TRUE;
    }

  top.t1 = t1;
  top.t2 = t2;
  top.next = info->compare_list;
  info->compare_list = &top;

  switch (t1->kind)
    {
    default:
      abort ();
      ret = FALSE;
      break;

    case DEBUG_KIND_STRUCT:
    case DEBUG_KIND_UNION:
    case DEBUG_KIND_CLASS:
    case DEBUG_KIND_UNION_CLASS:
      if (t1->u.kclass == NULL)
	ret = t2->u.kclass == NULL;
      else if (t2->u.kclass == NULL)
	ret = FALSE;
      else if (t1->u.kclass->id > info->base_id
	       && t1->u.kclass->id == t2->u.kclass->id)
	ret = TRUE;
      else
	ret = debug_class_type_samep (info, t1, t2);
      break;

    case DEBUG_KIND_ENUM:
      if (t1->u.kenum == NULL)
	ret = t2->u.kenum == NULL;
      else if (t2->u.kenum == NULL)
	ret = FALSE;
      else
	{
	  const char **pn1, **pn2;
	  bfd_signed_vma *pv1, *pv2;

	  pn1 = t1->u.kenum->names;
	  pn2 = t2->u.kenum->names;
	  pv1 = t1->u.kenum->values;
	  pv2 = t2->u.kenum->values;
	  while (*pn1 != NULL && *pn2 != NULL)
	    {
	      if (**pn1 != **pn2
		  || *pv1 != *pv2
		  || strcmp (*pn1, *pn2) != 0)
		break;
	      ++pn1;
	      ++pn2;
	      ++pv1;
	      ++pv2;
	    }
	  ret = *pn1 == NULL && *pn2 == NULL;
	}
      break;

    case DEBUG_KIND_POINTER:
      ret = debug_type_samep (info, t1->u.kpointer, t2->u.kpointer);
      break;

    case DEBUG_KIND_FUNCTION:
      if (t1->u.kfunction->varargs != t2->u.kfunction->varargs
	  || ! debug_type_samep (info, t1->u.kfunction->return_type,
				 t2->u.kfunction->return_type)
	  || ((t1->u.kfunction->arg_types == NULL)
	      != (t2->u.kfunction->arg_types == NULL)))
	ret = FALSE;
      else if (t1->u.kfunction->arg_types == NULL)
	ret = TRUE;
      else
	{
	  struct debug_type **a1, **a2;

	  a1 = t1->u.kfunction->arg_types;
	  a2 = t2->u.kfunction->arg_types;
	  while (*a1 != NULL && *a2 != NULL)
	    {
	      if (! debug_type_samep (info, *a1, *a2))
		break;
	      ++a1;
	      ++a2;
	    }
	  ret = *a1 == NULL && *a2 == NULL;
	}
      break;

    case DEBUG_KIND_REFERENCE:
      ret = debug_type_samep (info, t1->u.kreference, t2->u.kreference);
      break;

    case DEBUG_KIND_RANGE:
      ret = (t1->u.krange->lower == t2->u.krange->lower
	     && t1->u.krange->upper == t2->u.krange->upper
	     && debug_type_samep (info, t1->u.krange->type,
				  t2->u.krange->type));

    case DEBUG_KIND_ARRAY:
      ret = (t1->u.karray->lower == t2->u.karray->lower
	     && t1->u.karray->upper == t2->u.karray->upper
	     && t1->u.karray->stringp == t2->u.karray->stringp
	     && debug_type_samep (info, t1->u.karray->element_type,
				  t2->u.karray->element_type));
      break;

    case DEBUG_KIND_SET:
      ret = (t1->u.kset->bitstringp == t2->u.kset->bitstringp
	     && debug_type_samep (info, t1->u.kset->type, t2->u.kset->type));
      break;

    case DEBUG_KIND_OFFSET:
      ret = (debug_type_samep (info, t1->u.koffset->base_type,
			       t2->u.koffset->base_type)
	     && debug_type_samep (info, t1->u.koffset->target_type,
				  t2->u.koffset->target_type));
      break;

    case DEBUG_KIND_METHOD:
      if (t1->u.kmethod->varargs != t2->u.kmethod->varargs
	  || ! debug_type_samep (info, t1->u.kmethod->return_type,
				 t2->u.kmethod->return_type)
	  || ! debug_type_samep (info, t1->u.kmethod->domain_type,
				 t2->u.kmethod->domain_type)
	  || ((t1->u.kmethod->arg_types == NULL)
	      != (t2->u.kmethod->arg_types == NULL)))
	ret = FALSE;
      else if (t1->u.kmethod->arg_types == NULL)
	ret = TRUE;
      else
	{
	  struct debug_type **a1, **a2;

	  a1 = t1->u.kmethod->arg_types;
	  a2 = t2->u.kmethod->arg_types;
	  while (*a1 != NULL && *a2 != NULL)
	    {
	      if (! debug_type_samep (info, *a1, *a2))
		break;
	      ++a1;
	      ++a2;
	    }
	  ret = *a1 == NULL && *a2 == NULL;
	}
      break;

    case DEBUG_KIND_CONST:
      ret = debug_type_samep (info, t1->u.kconst, t2->u.kconst);
      break;

    case DEBUG_KIND_VOLATILE:
      ret = debug_type_samep (info, t1->u.kvolatile, t2->u.kvolatile);
      break;

    case DEBUG_KIND_NAMED:
    case DEBUG_KIND_TAGGED:
      ret = (strcmp (t1->u.knamed->name->name, t2->u.knamed->name->name) == 0
	     && debug_type_samep (info, t1->u.knamed->type,
				  t2->u.knamed->type));
      break;
    }

  info->compare_list = top.next;

  return ret;
}