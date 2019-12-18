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
struct value {int dummy; } ;
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
struct obstack {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_IGNORE (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_NAME (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_PACKED (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_STATIC (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 scalar_t__ TYPE_HAS_VTABLE (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 int /*<<< orphan*/  annotate_field_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  annotate_field_end () ; 
 int /*<<< orphan*/  annotate_field_name_end () ; 
 int /*<<< orphan*/  annotate_field_value () ; 
 int /*<<< orphan*/  builtin_type_unsigned_long ; 
 int /*<<< orphan*/  common_val_print (struct value*,struct ui_file*,int,int /*<<< orphan*/ ,int,int) ; 
 int count_virtual_fns (struct type*) ; 
 int /*<<< orphan*/  cp_print_hpacc_virtual_table_entries (struct type*,int*,struct value*,struct ui_file*,int,int,int) ; 
 int /*<<< orphan*/  cp_print_static_field (int /*<<< orphan*/ ,struct value*,struct ui_file*,int,int,int) ; 
 int /*<<< orphan*/  cp_print_value (struct type*,struct type*,char*,int,scalar_t__,struct ui_file*,int,int,int,struct type**) ; 
 struct obstack dont_print_statmem_obstack ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fprintf_symbol_filtered (struct ui_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  hpacc_vtbl_ptr_name ; 
 scalar_t__ inspect_it ; 
 int /*<<< orphan*/  language_cplus ; 
 int /*<<< orphan*/  lookup_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_spaces (int) ; 
 int /*<<< orphan*/  obstack_finish (struct obstack*) ; 
 int /*<<< orphan*/  obstack_free (struct obstack*,char*) ; 
 char* obstack_next_free (struct obstack*) ; 
 int /*<<< orphan*/  print_spaces_filtered (int,struct ui_file*) ; 
 int /*<<< orphan*/  static_field_print ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* type_name_no_tag (struct type*) ; 
 int /*<<< orphan*/  unpack_field_as_long (struct type*,char*,int) ; 
 int /*<<< orphan*/  val_print (int /*<<< orphan*/ ,char*,int,scalar_t__,struct ui_file*,int,int /*<<< orphan*/ ,int,int) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* value_from_pointer (int /*<<< orphan*/ ,unsigned long) ; 
 struct value* value_static_field (struct type*,int) ; 
 scalar_t__ vtblprint ; 
 int /*<<< orphan*/  wrap_here (int /*<<< orphan*/ ) ; 

void
cp_print_value_fields (struct type *type, struct type *real_type, char *valaddr,
		       int offset, CORE_ADDR address, struct ui_file *stream,
		       int format, int recurse, enum val_prettyprint pretty,
		       struct type **dont_print_vb, int dont_print_statmem)
{
  int i, len, n_baseclasses;
  struct obstack tmp_obstack;
  char *last_dont_print = obstack_next_free (&dont_print_statmem_obstack);
  int fields_seen = 0;

  CHECK_TYPEDEF (type);

  fprintf_filtered (stream, "{");
  len = TYPE_NFIELDS (type);
  n_baseclasses = TYPE_N_BASECLASSES (type);

  /* First, print out baseclasses such that we don't print
     duplicates of virtual baseclasses.  */

  if (n_baseclasses > 0)
    cp_print_value (type, real_type, valaddr, offset, address, stream,
		    format, recurse + 1, pretty, dont_print_vb);

  /* Second, print out data fields */

  /* If there are no data fields, or if the only field is the
   * vtbl pointer, skip this part */
  if ((len == n_baseclasses)
      || ((len - n_baseclasses == 1)
	  && TYPE_HAS_VTABLE (type)
	  && strncmp (TYPE_FIELD_NAME (type, n_baseclasses),
		      hpacc_vtbl_ptr_name, 5) == 0)
      || !len)
    fprintf_filtered (stream, "<No data fields>");
  else
    {
      if (dont_print_statmem == 0)
	{
	  /* If we're at top level, carve out a completely fresh
	     chunk of the obstack and use that until this particular
	     invocation returns.  */
	  tmp_obstack = dont_print_statmem_obstack;
	  obstack_finish (&dont_print_statmem_obstack);
	}

      for (i = n_baseclasses; i < len; i++)
	{
	  /* If requested, skip printing of static fields.  */
	  if (!static_field_print && TYPE_FIELD_STATIC (type, i))
	    continue;

	  /* If a vtable pointer appears, we'll print it out later */
	  if (TYPE_HAS_VTABLE (type)
	      && strncmp (TYPE_FIELD_NAME (type, i), hpacc_vtbl_ptr_name,
			  5) == 0)
	    continue;

	  if (fields_seen)
	    fprintf_filtered (stream, ", ");
	  else if (n_baseclasses > 0)
	    {
	      if (pretty)
		{
		  fprintf_filtered (stream, "\n");
		  print_spaces_filtered (2 + 2 * recurse, stream);
		  fputs_filtered ("members of ", stream);
		  fputs_filtered (type_name_no_tag (type), stream);
		  fputs_filtered (": ", stream);
		}
	    }
	  fields_seen = 1;

	  if (pretty)
	    {
	      fprintf_filtered (stream, "\n");
	      print_spaces_filtered (2 + 2 * recurse, stream);
	    }
	  else
	    {
	      wrap_here (n_spaces (2 + 2 * recurse));
	    }
	  if (inspect_it)
	    {
	      if (TYPE_CODE (TYPE_FIELD_TYPE (type, i)) == TYPE_CODE_PTR)
		fputs_filtered ("\"( ptr \"", stream);
	      else
		fputs_filtered ("\"( nodef \"", stream);
	      if (TYPE_FIELD_STATIC (type, i))
		fputs_filtered ("static ", stream);
	      fprintf_symbol_filtered (stream, TYPE_FIELD_NAME (type, i),
				       language_cplus,
				       DMGL_PARAMS | DMGL_ANSI);
	      fputs_filtered ("\" \"", stream);
	      fprintf_symbol_filtered (stream, TYPE_FIELD_NAME (type, i),
				       language_cplus,
				       DMGL_PARAMS | DMGL_ANSI);
	      fputs_filtered ("\") \"", stream);
	    }
	  else
	    {
	      annotate_field_begin (TYPE_FIELD_TYPE (type, i));

	      if (TYPE_FIELD_STATIC (type, i))
		fputs_filtered ("static ", stream);
	      fprintf_symbol_filtered (stream, TYPE_FIELD_NAME (type, i),
				       language_cplus,
				       DMGL_PARAMS | DMGL_ANSI);
	      annotate_field_name_end ();
	      /* do not print leading '=' in case of anonymous unions */
	      if (strcmp (TYPE_FIELD_NAME (type, i), ""))
		fputs_filtered (" = ", stream);
	      annotate_field_value ();
	    }

	  if (!TYPE_FIELD_STATIC (type, i) && TYPE_FIELD_PACKED (type, i))
	    {
	      struct value *v;

	      /* Bitfields require special handling, especially due to byte
	         order problems.  */
	      if (TYPE_FIELD_IGNORE (type, i))
		{
		  fputs_filtered ("<optimized out or zero length>", stream);
		}
	      else
		{
		  v = value_from_longest
		    (TYPE_FIELD_TYPE (type, i), 
		     unpack_field_as_long (type, valaddr + offset, i));

		  common_val_print (v, stream, format, 0, recurse + 1, pretty);
		}
	    }
	  else
	    {
	      if (TYPE_FIELD_IGNORE (type, i))
		{
		  fputs_filtered ("<optimized out or zero length>", stream);
		}
	      else if (TYPE_FIELD_STATIC (type, i))
		{
		  struct value *v = value_static_field (type, i);
		  if (v == NULL)
		    fputs_filtered ("<optimized out>", stream);
		  else
		    cp_print_static_field (TYPE_FIELD_TYPE (type, i), v,
					   stream, format, recurse + 1,
					   pretty);
		}
	      else
		{
		  val_print (TYPE_FIELD_TYPE (type, i),
			     valaddr, offset + TYPE_FIELD_BITPOS (type, i) / 8,
			     address + TYPE_FIELD_BITPOS (type, i) / 8,
			     stream, format, 0, recurse + 1, pretty);
		}
	    }
	  annotate_field_end ();
	}

      if (dont_print_statmem == 0)
	{
	  /* Free the space used to deal with the printing
	     of the members from top level.  */
	  obstack_free (&dont_print_statmem_obstack, last_dont_print);
	  dont_print_statmem_obstack = tmp_obstack;
	}

      if (pretty)
	{
	  fprintf_filtered (stream, "\n");
	  print_spaces_filtered (2 * recurse, stream);
	}
    }				/* if there are data fields */
  /* Now print out the virtual table pointer if there is one */
  if (TYPE_HAS_VTABLE (type)
      && strncmp (TYPE_FIELD_NAME (type, n_baseclasses),
		  hpacc_vtbl_ptr_name, 5) == 0)
    {
      struct value *v;
      /* First get the virtual table pointer and print it out */

#if 0
      fputs_filtered ("__vfp = ", stream);
#endif

      fputs_filtered (", Virtual table at ", stream);

      /* pai: FIXME 32x64 problem? */
      /* Not sure what the best notation is in the case where there is no
         baseclass name.  */
      v = value_from_pointer (lookup_pointer_type (builtin_type_unsigned_long),
			      *(unsigned long *) (valaddr + offset));

      common_val_print (v, stream, format, 0, recurse + 1, pretty);
      fields_seen = 1;

      if (vtblprint)
	{
	  /* Print out function pointers in vtable. */

	  /* FIXME: then-clause is for non-RRBC layout of virtual
	   * table.  The RRBC case in the else-clause is yet to be
	   * implemented.  The if (1) below should be changed to a
	   * test for whether the executable we have was compiled
	   * with a version of HP aCC that doesn't have RRBC
	   * support. */

	  if (1)
	    {
	      /* no RRBC support; function pointers embedded directly
                 in vtable */

	      int vfuncs = count_virtual_fns (real_type);

	      fputs_filtered (" {", stream);

	      /* FIXME : doesn't work at present */
#if 0
	      fprintf_filtered (stream, "%d entr%s: ", vfuncs,
				vfuncs == 1 ? "y" : "ies");
#else
	      fputs_filtered ("not implemented", stream);


#endif

	      /* recursive function that prints all virtual function entries */
#if 0
	      cp_print_hpacc_virtual_table_entries (real_type, &vfuncs, v,
						    stream, format, recurse,
						    pretty);
#endif
	      fputs_filtered ("}", stream);
	    }			/* non-RRBC case */
	  else
	    {
	      /* FIXME -- see comments above */
	      /* RRBC support present; function pointers are found
	       * by indirection through the class segment entries. */


	    }			/* RRBC case */
	}			/* if vtblprint */

      if (pretty)
	{
	  fprintf_filtered (stream, "\n");
	  print_spaces_filtered (2 * recurse, stream);
	}

    }				/* if vtable exists */

  fprintf_filtered (stream, "}");
}