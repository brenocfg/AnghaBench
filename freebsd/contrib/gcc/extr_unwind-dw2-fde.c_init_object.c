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
struct TYPE_7__ {size_t count; int sorted; scalar_t__ from_array; } ;
struct TYPE_8__ {TYPE_3__ b; } ;
struct TYPE_5__ {TYPE_2__* sort; int /*<<< orphan*/ * single; int /*<<< orphan*/ ** array; } ;
struct object {TYPE_4__ s; TYPE_1__ u; } ;
struct fde_accumulator {TYPE_2__* linear; } ;
typedef  int /*<<< orphan*/  fde ;
struct TYPE_6__ {int /*<<< orphan*/ * orig_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_fdes (struct object*,struct fde_accumulator*,int /*<<< orphan*/ *) ; 
 size_t classify_object_over_fdes (struct object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_fde_sort (struct object*,struct fde_accumulator*,size_t) ; 
 int /*<<< orphan*/  start_fde_sort (struct fde_accumulator*,size_t) ; 

__attribute__((used)) static inline void
init_object (struct object* ob)
{
  struct fde_accumulator accu;
  size_t count;

  count = ob->s.b.count;
  if (count == 0)
    {
      if (ob->s.b.from_array)
	{
	  fde **p = ob->u.array;
	  for (count = 0; *p; ++p)
	    count += classify_object_over_fdes (ob, *p);
	}
      else
	count = classify_object_over_fdes (ob, ob->u.single);

      /* The count field we have in the main struct object is somewhat
	 limited, but should suffice for virtually all cases.  If the
	 counted value doesn't fit, re-write a zero.  The worst that
	 happens is that we re-count next time -- admittedly non-trivial
	 in that this implies some 2M fdes, but at least we function.  */
      ob->s.b.count = count;
      if (ob->s.b.count != count)
	ob->s.b.count = 0;
    }

  if (!start_fde_sort (&accu, count))
    return;

  if (ob->s.b.from_array)
    {
      fde **p;
      for (p = ob->u.array; *p; ++p)
	add_fdes (ob, &accu, *p);
    }
  else
    add_fdes (ob, &accu, ob->u.single);

  end_fde_sort (ob, &accu, count);

  /* Save the original fde pointer, since this is the key by which the
     DSO will deregister the object.  */
  accu.linear->orig_data = ob->u.single;
  ob->u.sort = accu.linear;

  ob->s.b.sorted = 1;
}