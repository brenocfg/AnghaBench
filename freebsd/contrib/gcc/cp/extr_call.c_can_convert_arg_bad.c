#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  conversion ;

/* Variables and functions */
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  conversion_obstack ; 
 void* conversion_obstack_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * implicit_conversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 

bool
can_convert_arg_bad (tree to, tree from, tree arg)
{
  conversion *t;
  void *p;

  /* Get the high-water mark for the CONVERSION_OBSTACK.  */
  p = conversion_obstack_alloc (0);
  /* Try to perform the conversion.  */
  t  = implicit_conversion (to, from, arg, /*c_cast_p=*/false,
			    LOOKUP_NORMAL);
  /* Free all the conversions we allocated.  */
  obstack_free (&conversion_obstack, p);

  return t != NULL;
}