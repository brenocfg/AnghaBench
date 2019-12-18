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
typedef  int LONGEST ;

/* Variables and functions */
 int HOST_CHAR_BIT ; 
 unsigned long TYPE_FIELD_BITSIZE (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 unsigned int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 struct value* ada_value_primitive_packed_val (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned long,struct type*) ; 
 int /*<<< orphan*/  annotate_array_section_begin (unsigned int,struct type*) ; 
 int /*<<< orphan*/  annotate_array_section_end () ; 
 int /*<<< orphan*/  annotate_elt () ; 
 int /*<<< orphan*/  annotate_elt_rep (unsigned int) ; 
 int /*<<< orphan*/  annotate_elt_rep_end () ; 
 int /*<<< orphan*/  check_typedef (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 scalar_t__ get_discrete_bounds (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  n_spaces (int) ; 
 scalar_t__ prettyprint_arrays ; 
 unsigned int print_max ; 
 int /*<<< orphan*/  print_spaces_filtered (int,struct ui_file*) ; 
 unsigned int repeat_count_threshold ; 
 int /*<<< orphan*/  val_print (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ui_file*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  value_free_to_mark (struct value*) ; 
 struct value* value_mark () ; 
 int /*<<< orphan*/  wrap_here (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
val_print_packed_array_elements (struct type *type, char *valaddr,
				 int bitoffset, struct ui_file *stream,
				 int format, int recurse,
				 enum val_prettyprint pretty)
{
  unsigned int i;
  unsigned int things_printed = 0;
  unsigned len;
  struct type *elttype;
  unsigned eltlen;
  /* Position of the array element we are examining to see
     whether it is repeated.  */
  unsigned int rep1;
  /* Number of repetitions we have detected so far.  */
  unsigned int reps;
  unsigned long bitsize = TYPE_FIELD_BITSIZE (type, 0);
  struct value *mark = value_mark ();

  elttype = TYPE_TARGET_TYPE (type);
  eltlen = TYPE_LENGTH (check_typedef (elttype));

  {
    LONGEST low, high;
    if (get_discrete_bounds (TYPE_FIELD_TYPE (type, 0), &low, &high) < 0)
      len = 1;
    else
      len = high - low + 1;
  }

  i = 0;
  annotate_array_section_begin (i, elttype);

  while (i < len && things_printed < print_max)
    {
      struct value *v0, *v1;
      int i0;

      if (i != 0)
	{
	  if (prettyprint_arrays)
	    {
	      fprintf_filtered (stream, ",\n");
	      print_spaces_filtered (2 + 2 * recurse, stream);
	    }
	  else
	    {
	      fprintf_filtered (stream, ", ");
	    }
	}
      wrap_here (n_spaces (2 + 2 * recurse));

      i0 = i;
      v0 = ada_value_primitive_packed_val (NULL, valaddr,
					   (i0 * bitsize) / HOST_CHAR_BIT,
					   (i0 * bitsize) % HOST_CHAR_BIT,
					   bitsize, elttype);
      while (1)
	{
	  i += 1;
	  if (i >= len)
	    break;
	  v1 = ada_value_primitive_packed_val (NULL, valaddr,
					       (i * bitsize) / HOST_CHAR_BIT,
					       (i * bitsize) % HOST_CHAR_BIT,
					       bitsize, elttype);
	  if (memcmp (VALUE_CONTENTS (v0), VALUE_CONTENTS (v1), eltlen) != 0)
	    break;
	}

      if (i - i0 > repeat_count_threshold)
	{
	  val_print (elttype, VALUE_CONTENTS (v0), 0, 0, stream, format,
		     0, recurse + 1, pretty);
	  annotate_elt_rep (i - i0);
	  fprintf_filtered (stream, " <repeats %u times>", i - i0);
	  annotate_elt_rep_end ();

	}
      else
	{
	  int j;
	  for (j = i0; j < i; j += 1)
	    {
	      if (j > i0)
		{
		  if (prettyprint_arrays)
		    {
		      fprintf_filtered (stream, ",\n");
		      print_spaces_filtered (2 + 2 * recurse, stream);
		    }
		  else
		    {
		      fprintf_filtered (stream, ", ");
		    }
		  wrap_here (n_spaces (2 + 2 * recurse));
		}
	      val_print (elttype, VALUE_CONTENTS (v0), 0, 0, stream, format,
			 0, recurse + 1, pretty);
	      annotate_elt ();
	    }
	}
      things_printed += i - i0;
    }
  annotate_array_section_end ();
  if (i < len)
    {
      fprintf_filtered (stream, "...");
    }

  value_free_to_mark (mark);
}