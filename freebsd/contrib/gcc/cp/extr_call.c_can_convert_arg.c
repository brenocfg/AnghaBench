#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  bad_p; } ;
typedef  TYPE_1__ conversion ;

/* Variables and functions */
 int /*<<< orphan*/  conversion_obstack ; 
 void* conversion_obstack_alloc (int /*<<< orphan*/ ) ; 
 TYPE_1__* implicit_conversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 

bool
can_convert_arg (tree to, tree from, tree arg, int flags)
{
  conversion *t;
  void *p;
  bool ok_p;

  /* Get the high-water mark for the CONVERSION_OBSTACK.  */
  p = conversion_obstack_alloc (0);

  t  = implicit_conversion (to, from, arg, /*c_cast_p=*/false,
			    flags);
  ok_p = (t && !t->bad_p);

  /* Free all the conversions we allocated.  */
  obstack_free (&conversion_obstack, p);

  return ok_p;
}