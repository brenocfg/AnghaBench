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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int F77_DIM_OFFSET (int) ; 
 int F77_DIM_SIZE (int) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int print_max ; 
 int /*<<< orphan*/  val_print (struct type*,char*,int /*<<< orphan*/ ,scalar_t__,struct ui_file*,int,int,int,int) ; 

__attribute__((used)) static void
f77_print_array_1 (int nss, int ndimensions, struct type *type, char *valaddr,
		   CORE_ADDR address, struct ui_file *stream, int format,
		   int deref_ref, int recurse, enum val_prettyprint pretty,
		   int *elts)
{
  int i;

  if (nss != ndimensions)
    {
      for (i = 0; (i < F77_DIM_SIZE (nss) && (*elts) < print_max); i++)
	{
	  fprintf_filtered (stream, "( ");
	  f77_print_array_1 (nss + 1, ndimensions, TYPE_TARGET_TYPE (type),
			     valaddr + i * F77_DIM_OFFSET (nss),
			     address + i * F77_DIM_OFFSET (nss),
			     stream, format, deref_ref, recurse, pretty, elts);
	  fprintf_filtered (stream, ") ");
	}
      if (*elts >= print_max && i < F77_DIM_SIZE (nss)) 
	fprintf_filtered (stream, "...");
    }
  else
    {
      for (i = 0; i < F77_DIM_SIZE (nss) && (*elts) < print_max; 
	   i++, (*elts)++)
	{
	  val_print (TYPE_TARGET_TYPE (type),
		     valaddr + i * F77_DIM_OFFSET (ndimensions),
		     0,
		     address + i * F77_DIM_OFFSET (ndimensions),
		     stream, format, deref_ref, recurse, pretty);

	  if (i != (F77_DIM_SIZE (nss) - 1))
	    fprintf_filtered (stream, ", ");

	  if ((*elts == print_max - 1) && (i != (F77_DIM_SIZE (nss) - 1)))
	    fprintf_filtered (stream, "...");
	}
    }
}