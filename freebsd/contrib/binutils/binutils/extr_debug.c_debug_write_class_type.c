#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct debug_write_fns {int /*<<< orphan*/  (* end_class_type ) (void*) ;int /*<<< orphan*/  (* class_end_method ) (void*) ;int /*<<< orphan*/  (* class_static_method_variant ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* class_method_variant ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* class_start_method ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* class_baseclass ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* struct_field ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* class_static_member ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_class_type ) (void*,char const*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* tag_type ) (void*,char const*,unsigned int,scalar_t__) ;} ;
struct TYPE_10__ {TYPE_4__* kclass; } ;
struct debug_type {scalar_t__ kind; TYPE_5__ u; int /*<<< orphan*/  size; } ;
struct debug_name {int dummy; } ;
struct debug_method_variant {scalar_t__ voffset; int /*<<< orphan*/  volatilep; int /*<<< orphan*/  constp; int /*<<< orphan*/  visibility; int /*<<< orphan*/  physname; struct debug_type* context; struct debug_type* type; } ;
struct debug_method {struct debug_method_variant** variants; int /*<<< orphan*/  name; } ;
struct debug_handle {unsigned int base_id; scalar_t__ mark; } ;
struct TYPE_7__ {int /*<<< orphan*/  bitsize; int /*<<< orphan*/  bitpos; } ;
struct TYPE_6__ {int /*<<< orphan*/  physname; } ;
struct TYPE_8__ {TYPE_2__ f; TYPE_1__ s; } ;
struct debug_field {int /*<<< orphan*/  visibility; TYPE_3__ u; int /*<<< orphan*/  name; scalar_t__ static_member; struct debug_type* type; } ;
struct debug_baseclass {int /*<<< orphan*/  visibility; int /*<<< orphan*/  virtual; int /*<<< orphan*/  bitpos; struct debug_type* type; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {unsigned int id; scalar_t__ mark; struct debug_method** methods; struct debug_baseclass** baseclasses; struct debug_field** fields; struct debug_type* vptrbase; } ;

/* Variables and functions */
 scalar_t__ DEBUG_KIND_CLASS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ VOFFSET_STATIC_METHOD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug_set_class_id (struct debug_handle*,char const*,struct debug_type*) ; 
 int /*<<< orphan*/  debug_write_type (struct debug_handle*,struct debug_write_fns const*,void*,struct debug_type*,struct debug_name*) ; 
 int /*<<< orphan*/  stub1 (void*,char const*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  stub10 (void*) ; 
 int /*<<< orphan*/  stub2 (void*,char const*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (void*) ; 

__attribute__((used)) static bfd_boolean
debug_write_class_type (struct debug_handle *info,
			const struct debug_write_fns *fns, void *fhandle,
			struct debug_type *type, const char *tag)
{
  unsigned int i;
  unsigned int id;
  struct debug_type *vptrbase;

  if (type->u.kclass == NULL)
    {
      id = 0;
      vptrbase = NULL;
    }
  else
    {
      if (type->u.kclass->id <= info->base_id)
	{
	  if (! debug_set_class_id (info, tag, type))
	    return FALSE;
	}

      if (info->mark == type->u.kclass->mark)
	{
	  /* We are currently outputting this class, or we have
	     already output it.  This can happen when there are
	     methods for an anonymous class.  */
	  assert (type->u.kclass->id > info->base_id);
	  return (*fns->tag_type) (fhandle, tag, type->u.kclass->id,
				   type->kind);
	}
      type->u.kclass->mark = info->mark;
      id = type->u.kclass->id;

      vptrbase = type->u.kclass->vptrbase;
      if (vptrbase != NULL && vptrbase != type)
	{
	  if (! debug_write_type (info, fns, fhandle, vptrbase,
				  (struct debug_name *) NULL))
	    return FALSE;
	}
    }

  if (! (*fns->start_class_type) (fhandle, tag, id,
				  type->kind == DEBUG_KIND_CLASS,
				  type->size,
				  vptrbase != NULL,
				  vptrbase == type))
    return FALSE;

  if (type->u.kclass != NULL)
    {
      if (type->u.kclass->fields != NULL)
	{
	  for (i = 0; type->u.kclass->fields[i] != NULL; i++)
	    {
	      struct debug_field *f;

	      f = type->u.kclass->fields[i];
	      if (! debug_write_type (info, fns, fhandle, f->type,
				      (struct debug_name *) NULL))
		return FALSE;
	      if (f->static_member)
		{
		  if (! (*fns->class_static_member) (fhandle, f->name,
						     f->u.s.physname,
						     f->visibility))
		    return FALSE;
		}
	      else
		{
		  if (! (*fns->struct_field) (fhandle, f->name, f->u.f.bitpos,
					      f->u.f.bitsize, f->visibility))
		    return FALSE;
		}
	    }
	}

      if (type->u.kclass->baseclasses != NULL)
	{
	  for (i = 0; type->u.kclass->baseclasses[i] != NULL; i++)
	    {
	      struct debug_baseclass *b;

	      b = type->u.kclass->baseclasses[i];
	      if (! debug_write_type (info, fns, fhandle, b->type,
				      (struct debug_name *) NULL))
		return FALSE;
	      if (! (*fns->class_baseclass) (fhandle, b->bitpos, b->virtual,
					     b->visibility))
		return FALSE;
	    }
	}

      if (type->u.kclass->methods != NULL)
	{
	  for (i = 0; type->u.kclass->methods[i] != NULL; i++)
	    {
	      struct debug_method *m;
	      unsigned int j;

	      m = type->u.kclass->methods[i];
	      if (! (*fns->class_start_method) (fhandle, m->name))
		return FALSE;
	      for (j = 0; m->variants[j] != NULL; j++)
		{
		  struct debug_method_variant *v;

		  v = m->variants[j];
		  if (v->context != NULL)
		    {
		      if (! debug_write_type (info, fns, fhandle, v->context,
					      (struct debug_name *) NULL))
			return FALSE;
		    }
		  if (! debug_write_type (info, fns, fhandle, v->type,
					  (struct debug_name *) NULL))
		    return FALSE;
		  if (v->voffset != VOFFSET_STATIC_METHOD)
		    {
		      if (! (*fns->class_method_variant) (fhandle, v->physname,
							  v->visibility,
							  v->constp,
							  v->volatilep,
							  v->voffset,
							  v->context != NULL))
			return FALSE;
		    }
		  else
		    {
		      if (! (*fns->class_static_method_variant) (fhandle,
								 v->physname,
								 v->visibility,
								 v->constp,
								 v->volatilep))
			return FALSE;
		    }
		}
	      if (! (*fns->class_end_method) (fhandle))
		return FALSE;
	    }
	}
    }

  return (*fns->end_class_type) (fhandle);
}