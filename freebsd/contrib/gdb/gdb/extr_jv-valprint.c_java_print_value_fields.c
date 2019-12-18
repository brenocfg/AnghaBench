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
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BASETYPE_VIA_VIRTUAL (struct type*,int) ; 
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 int /*<<< orphan*/  TYPE_BASECLASS (struct type*,int) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_IGNORE (struct type*,int) ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_PACKED (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_STATIC (struct type*,int) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 char* TYPE_NAME (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  annotate_field_begin (struct type*) ; 
 int /*<<< orphan*/  annotate_field_end () ; 
 int /*<<< orphan*/  annotate_field_name_end () ; 
 int /*<<< orphan*/  annotate_field_value () ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_val_print (struct value*,struct ui_file*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  fprintf_symbol_filtered (struct ui_file*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 scalar_t__ inspect_it ; 
 int /*<<< orphan*/  language_cplus ; 
 int /*<<< orphan*/  n_spaces (int) ; 
 int /*<<< orphan*/  print_spaces_filtered (int,struct ui_file*) ; 
 int /*<<< orphan*/  static_field_print ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* type_name_no_tag (struct type*) ; 
 int /*<<< orphan*/  unpack_field_as_long (struct type*,char*,int) ; 
 int /*<<< orphan*/  val_print (struct type*,char*,int /*<<< orphan*/ ,scalar_t__,struct ui_file*,int,int /*<<< orphan*/ ,int,int) ; 
 struct value* value_addr (struct value*) ; 
 struct value* value_from_longest (struct type*,int /*<<< orphan*/ ) ; 
 struct value* value_static_field (struct type*,int) ; 
 int /*<<< orphan*/  wrap_here (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
java_print_value_fields (struct type *type, char *valaddr, CORE_ADDR address,
			 struct ui_file *stream, int format, int recurse,
			 enum val_prettyprint pretty)
{
  int i, len, n_baseclasses;

  CHECK_TYPEDEF (type);

  fprintf_filtered (stream, "{");
  len = TYPE_NFIELDS (type);
  n_baseclasses = TYPE_N_BASECLASSES (type);

  if (n_baseclasses > 0)
    {
      int i, n_baseclasses = TYPE_N_BASECLASSES (type);

      for (i = 0; i < n_baseclasses; i++)
	{
	  int boffset;
	  struct type *baseclass = check_typedef (TYPE_BASECLASS (type, i));
	  char *basename = TYPE_NAME (baseclass);
	  char *base_valaddr;

	  if (BASETYPE_VIA_VIRTUAL (type, i))
	    continue;

	  if (basename != NULL && strcmp (basename, "java.lang.Object") == 0)
	    continue;

	  boffset = 0;

	  if (pretty)
	    {
	      fprintf_filtered (stream, "\n");
	      print_spaces_filtered (2 * (recurse + 1), stream);
	    }
	  fputs_filtered ("<", stream);
	  /* Not sure what the best notation is in the case where there is no
	     baseclass name.  */
	  fputs_filtered (basename ? basename : "", stream);
	  fputs_filtered ("> = ", stream);

	  base_valaddr = valaddr;

	  java_print_value_fields (baseclass, base_valaddr, address + boffset,
				   stream, format, recurse + 1, pretty);
	  fputs_filtered (", ", stream);
	}

    }

  if (!len && n_baseclasses == 1)
    fprintf_filtered (stream, "<No data fields>");
  else
    {
      int fields_seen = 0;

      for (i = n_baseclasses; i < len; i++)
	{
	  /* If requested, skip printing of static fields.  */
	  if (TYPE_FIELD_STATIC (type, i))
	    {
	      char *name = TYPE_FIELD_NAME (type, i);
	      if (!static_field_print)
		continue;
	      if (name != NULL && strcmp (name, "class") == 0)
		continue;
	    }
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
	      fputs_filtered (": ", stream);
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
		  v = value_from_longest (TYPE_FIELD_TYPE (type, i),
				   unpack_field_as_long (type, valaddr, i));

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
		    {
		      struct type *t = check_typedef (VALUE_TYPE (v));
		      if (TYPE_CODE (t) == TYPE_CODE_STRUCT)
			v = value_addr (v);
		      common_val_print (v, stream, format, 0, recurse + 1,
					pretty);
		    }
		}
	      else if (TYPE_FIELD_TYPE (type, i) == NULL)
		fputs_filtered ("<unknown type>", stream);
	      else
		{
		  val_print (TYPE_FIELD_TYPE (type, i),
			     valaddr + TYPE_FIELD_BITPOS (type, i) / 8, 0,
			     address + TYPE_FIELD_BITPOS (type, i) / 8,
			     stream, format, 0, recurse + 1, pretty);
		}
	    }
	  annotate_field_end ();
	}

      if (pretty)
	{
	  fprintf_filtered (stream, "\n");
	  print_spaces_filtered (2 * recurse, stream);
	}
    }
  fprintf_filtered (stream, "}");
}