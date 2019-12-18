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
struct ieee_type {int /*<<< orphan*/ * type; void** pslot; } ;
struct TYPE_2__ {unsigned int alloc; struct ieee_type* types; } ;
struct ieee_info {int /*<<< orphan*/  dhandle; TYPE_1__ types; } ;
typedef  void* debug_type ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 void* DEBUG_TYPE_NULL ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * debug_make_indirect_type (int /*<<< orphan*/ ,void**,char const*) ; 
 int /*<<< orphan*/  memset (struct ieee_type*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (struct ieee_type*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
ieee_alloc_type (struct ieee_info *info, unsigned int indx, bfd_boolean ref)
{
  unsigned int nalloc;
  register struct ieee_type *t;
  struct ieee_type *tend;

  if (indx >= info->types.alloc)
    {
      nalloc = info->types.alloc;
      if (nalloc == 0)
	nalloc = 4;
      while (indx >= nalloc)
	nalloc *= 2;

      info->types.types = ((struct ieee_type *)
			   xrealloc (info->types.types,
				     nalloc * sizeof *info->types.types));

      memset (info->types.types + info->types.alloc, 0,
	      (nalloc - info->types.alloc) * sizeof *info->types.types);

      tend = info->types.types + nalloc;
      for (t = info->types.types + info->types.alloc; t < tend; t++)
	t->type = DEBUG_TYPE_NULL;

      info->types.alloc = nalloc;
    }

  if (ref)
    {
      t = info->types.types + indx;
      if (t->type == NULL)
	{
	  t->pslot = (debug_type *) xmalloc (sizeof *t->pslot);
	  *t->pslot = DEBUG_TYPE_NULL;
	  t->type = debug_make_indirect_type (info->dhandle, t->pslot,
					      (const char *) NULL);
	  if (t->type == NULL)
	    return FALSE;
	}
    }

  return TRUE;
}