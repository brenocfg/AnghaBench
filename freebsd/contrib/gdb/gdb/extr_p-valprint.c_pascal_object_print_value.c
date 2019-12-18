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
struct obstack {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BASETYPE_VIA_VIRTUAL (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_BASECLASS (struct type*,int) ; 
 int TYPE_LENGTH (struct type*) ; 
 char* TYPE_NAME (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 scalar_t__ alloca (int) ; 
 int baseclass_offset (struct type*,int,char*,scalar_t__) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 struct obstack dont_print_vb_obstack ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 scalar_t__ obstack_base (struct obstack*) ; 
 int /*<<< orphan*/  obstack_finish (struct obstack*) ; 
 int /*<<< orphan*/  obstack_free (struct obstack*,struct type**) ; 
 scalar_t__ obstack_next_free (struct obstack*) ; 
 int /*<<< orphan*/  obstack_ptr_grow (struct obstack*,struct type*) ; 
 int /*<<< orphan*/  pascal_object_print_value_fields (struct type*,char*,scalar_t__,struct ui_file*,int,int,int,struct type**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_spaces_filtered (int,struct ui_file*) ; 
 scalar_t__ target_read_memory (scalar_t__,char*,int) ; 

void
pascal_object_print_value (struct type *type, char *valaddr, CORE_ADDR address,
			   struct ui_file *stream, int format, int recurse,
			   enum val_prettyprint pretty,
			   struct type **dont_print_vb)
{
  struct obstack tmp_obstack;
  struct type **last_dont_print
  = (struct type **) obstack_next_free (&dont_print_vb_obstack);
  int i, n_baseclasses = TYPE_N_BASECLASSES (type);

  if (dont_print_vb == 0)
    {
      /* If we're at top level, carve out a completely fresh
         chunk of the obstack and use that until this particular
         invocation returns.  */
      tmp_obstack = dont_print_vb_obstack;
      /* Bump up the high-water mark.  Now alpha is omega.  */
      obstack_finish (&dont_print_vb_obstack);
    }

  for (i = 0; i < n_baseclasses; i++)
    {
      int boffset;
      struct type *baseclass = check_typedef (TYPE_BASECLASS (type, i));
      char *basename = TYPE_NAME (baseclass);
      char *base_valaddr;

      if (BASETYPE_VIA_VIRTUAL (type, i))
	{
	  struct type **first_dont_print
	  = (struct type **) obstack_base (&dont_print_vb_obstack);

	  int j = (struct type **) obstack_next_free (&dont_print_vb_obstack)
	  - first_dont_print;

	  while (--j >= 0)
	    if (baseclass == first_dont_print[j])
	      goto flush_it;

	  obstack_ptr_grow (&dont_print_vb_obstack, baseclass);
	}

      boffset = baseclass_offset (type, i, valaddr, address);

      if (pretty)
	{
	  fprintf_filtered (stream, "\n");
	  print_spaces_filtered (2 * recurse, stream);
	}
      fputs_filtered ("<", stream);
      /* Not sure what the best notation is in the case where there is no
         baseclass name.  */

      fputs_filtered (basename ? basename : "", stream);
      fputs_filtered ("> = ", stream);

      /* The virtual base class pointer might have been clobbered by the
         user program. Make sure that it still points to a valid memory
         location.  */

      if (boffset != -1 && (boffset < 0 || boffset >= TYPE_LENGTH (type)))
	{
	  /* FIXME (alloc): not safe is baseclass is really really big. */
	  base_valaddr = (char *) alloca (TYPE_LENGTH (baseclass));
	  if (target_read_memory (address + boffset, base_valaddr,
				  TYPE_LENGTH (baseclass)) != 0)
	    boffset = -1;
	}
      else
	base_valaddr = valaddr + boffset;

      if (boffset == -1)
	fprintf_filtered (stream, "<invalid address>");
      else
	pascal_object_print_value_fields (baseclass, base_valaddr, address + boffset,
					  stream, format, recurse, pretty,
		     (struct type **) obstack_base (&dont_print_vb_obstack),
					  0);
      fputs_filtered (", ", stream);

    flush_it:
      ;
    }

  if (dont_print_vb == 0)
    {
      /* Free the space used to deal with the printing
         of this type from top level.  */
      obstack_free (&dont_print_vb_obstack, last_dont_print);
      /* Reset watermark so that we can continue protecting
         ourselves from whatever we were protecting ourselves.  */
      dont_print_vb_obstack = tmp_obstack;
    }
}