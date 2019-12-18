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
struct TYPE_4__ {int /*<<< orphan*/ * single; int /*<<< orphan*/ ** array; } ;
struct TYPE_5__ {scalar_t__ encoding; scalar_t__ from_array; scalar_t__ mixed_encoding; scalar_t__ sorted; } ;
struct TYPE_6__ {TYPE_2__ b; } ;
struct object {void* pc_begin; TYPE_1__ u; TYPE_3__ s; } ;
typedef  int /*<<< orphan*/  fde ;

/* Variables and functions */
 scalar_t__ DW_EH_PE_absptr ; 
 int /*<<< orphan*/  const* binary_search_mixed_encoding_fdes (struct object*,void*) ; 
 int /*<<< orphan*/  const* binary_search_single_encoding_fdes (struct object*,void*) ; 
 int /*<<< orphan*/  const* binary_search_unencoded_fdes (struct object*,void*) ; 
 int /*<<< orphan*/  init_object (struct object*) ; 
 int /*<<< orphan*/  const* linear_search_fdes (struct object*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static const fde *
search_object (struct object* ob, void *pc)
{
  /* If the data hasn't been sorted, try to do this now.  We may have
     more memory available than last time we tried.  */
  if (! ob->s.b.sorted)
    {
      init_object (ob);

      /* Despite the above comment, the normal reason to get here is
	 that we've not processed this object before.  A quick range
	 check is in order.  */
      if (pc < ob->pc_begin)
	return NULL;
    }

  if (ob->s.b.sorted)
    {
      if (ob->s.b.mixed_encoding)
	return binary_search_mixed_encoding_fdes (ob, pc);
      else if (ob->s.b.encoding == DW_EH_PE_absptr)
	return binary_search_unencoded_fdes (ob, pc);
      else
	return binary_search_single_encoding_fdes (ob, pc);
    }
  else
    {
      /* Long slow labourious linear search, cos we've no memory.  */
      if (ob->s.b.from_array)
	{
	  fde **p;
	  for (p = ob->u.array; *p ; p++)
	    {
	      const fde *f = linear_search_fdes (ob, *p, pc);
	      if (f)
		return f;
	    }
	  return NULL;
	}
      else
	return linear_search_fdes (ob, ob->u.single, pc);
    }
}