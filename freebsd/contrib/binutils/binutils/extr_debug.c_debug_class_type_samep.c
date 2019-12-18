#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct debug_class_type* kclass; } ;
struct debug_type {TYPE_1__ u; } ;
struct debug_method_variant {scalar_t__* physname; scalar_t__ visibility; scalar_t__ constp; scalar_t__ volatilep; scalar_t__ voffset; int /*<<< orphan*/ * context; int /*<<< orphan*/ * type; } ;
struct debug_method {scalar_t__* name; struct debug_method_variant** variants; } ;
struct debug_handle {int dummy; } ;
struct TYPE_7__ {scalar_t__ bitpos; scalar_t__ bitsize; } ;
struct TYPE_6__ {scalar_t__* physname; } ;
struct TYPE_8__ {TYPE_3__ f; TYPE_2__ s; } ;
struct debug_field {scalar_t__* name; scalar_t__ visibility; scalar_t__ static_member; int /*<<< orphan*/  type; TYPE_4__ u; } ;
struct debug_class_type {struct debug_method** methods; struct debug_baseclass** baseclasses; int /*<<< orphan*/ * vptrbase; struct debug_field** fields; } ;
struct debug_baseclass {scalar_t__ bitpos; scalar_t__ virtual; scalar_t__ visibility; int /*<<< orphan*/ * type; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * debug_get_real_type (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_type_samep (struct debug_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static bfd_boolean
debug_class_type_samep (struct debug_handle *info, struct debug_type *t1,
			struct debug_type *t2)
{
  struct debug_class_type *c1, *c2;

  c1 = t1->u.kclass;
  c2 = t2->u.kclass;

  if ((c1->fields == NULL) != (c2->fields == NULL)
      || (c1->baseclasses == NULL) != (c2->baseclasses == NULL)
      || (c1->methods == NULL) != (c2->methods == NULL)
      || (c1->vptrbase == NULL) != (c2->vptrbase == NULL))
    return FALSE;

  if (c1->fields != NULL)
    {
      struct debug_field **pf1, **pf2;

      for (pf1 = c1->fields, pf2 = c2->fields;
	   *pf1 != NULL && *pf2 != NULL;
	   pf1++, pf2++)
	{
	  struct debug_field *f1, *f2;

	  f1 = *pf1;
	  f2 = *pf2;
	  if (f1->name[0] != f2->name[0]
	      || f1->visibility != f2->visibility
	      || f1->static_member != f2->static_member)
	    return FALSE;
	  if (f1->static_member)
	    {
	      if (strcmp (f1->u.s.physname, f2->u.s.physname) != 0)
		return FALSE;
	    }
	  else
	    {
	      if (f1->u.f.bitpos != f2->u.f.bitpos
		  || f1->u.f.bitsize != f2->u.f.bitsize)
		return FALSE;
	    }
	  /* We do the checks which require function calls last.  We
             don't require that the types of fields have the same
             names, since that sometimes fails in the presence of
             typedefs and we really don't care.  */
	  if (strcmp (f1->name, f2->name) != 0
	      || ! debug_type_samep (info,
				     debug_get_real_type ((void *) info,
							  f1->type, NULL),
				     debug_get_real_type ((void *) info,
							  f2->type, NULL)))
	    return FALSE;
	}
      if (*pf1 != NULL || *pf2 != NULL)
	return FALSE;
    }

  if (c1->vptrbase != NULL)
    {
      if (! debug_type_samep (info, c1->vptrbase, c2->vptrbase))
	return FALSE;
    }

  if (c1->baseclasses != NULL)
    {
      struct debug_baseclass **pb1, **pb2;

      for (pb1 = c1->baseclasses, pb2 = c2->baseclasses;
	   *pb1 != NULL && *pb2 != NULL;
	   ++pb1, ++pb2)
	{
	  struct debug_baseclass *b1, *b2;

	  b1 = *pb1;
	  b2 = *pb2;
	  if (b1->bitpos != b2->bitpos
	      || b1->virtual != b2->virtual
	      || b1->visibility != b2->visibility
	      || ! debug_type_samep (info, b1->type, b2->type))
	    return FALSE;
	}
      if (*pb1 != NULL || *pb2 != NULL)
	return FALSE;
    }

  if (c1->methods != NULL)
    {
      struct debug_method **pm1, **pm2;

      for (pm1 = c1->methods, pm2 = c2->methods;
	   *pm1 != NULL && *pm2 != NULL;
	   ++pm1, ++pm2)
	{
	  struct debug_method *m1, *m2;

	  m1 = *pm1;
	  m2 = *pm2;
	  if (m1->name[0] != m2->name[0]
	      || strcmp (m1->name, m2->name) != 0
	      || (m1->variants == NULL) != (m2->variants == NULL))
	    return FALSE;
	  if (m1->variants == NULL)
	    {
	      struct debug_method_variant **pv1, **pv2;

	      for (pv1 = m1->variants, pv2 = m2->variants;
		   *pv1 != NULL && *pv2 != NULL;
		   ++pv1, ++pv2)
		{
		  struct debug_method_variant *v1, *v2;

		  v1 = *pv1;
		  v2 = *pv2;
		  if (v1->physname[0] != v2->physname[0]
		      || v1->visibility != v2->visibility
		      || v1->constp != v2->constp
		      || v1->volatilep != v2->volatilep
		      || v1->voffset != v2->voffset
		      || (v1->context == NULL) != (v2->context == NULL)
		      || strcmp (v1->physname, v2->physname) != 0
		      || ! debug_type_samep (info, v1->type, v2->type))
		    return FALSE;
		  if (v1->context != NULL)
		    {
		      if (! debug_type_samep (info, v1->context,
					      v2->context))
			return FALSE;
		    }
		}
	      if (*pv1 != NULL || *pv2 != NULL)
		return FALSE;
	    }
	}
      if (*pm1 != NULL || *pm2 != NULL)
	return FALSE;
    }

  return TRUE;
}