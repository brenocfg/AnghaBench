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

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 int TYPE_FIELD_BITSIZE (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELD_NAME (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_INDEX_TYPE (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int ada_array_arity (struct type*) ; 
 int /*<<< orphan*/  ada_array_element_type (struct type*,int) ; 
 struct type* ada_coerce_to_simple_array_type (struct type*) ; 
 struct type* ada_find_parallel_type (struct type*,char*) ; 
 scalar_t__ ada_is_packed_array_type (struct type*) ; 
 scalar_t__ ada_is_simple_array (struct type*) ; 
 int /*<<< orphan*/  ada_print_type (int /*<<< orphan*/ ,char*,struct ui_file*,int,int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  print_range (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  print_range_type_named (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
print_array_type (struct type *type, struct ui_file *stream, int show,
		  int level)
{
  int bitsize;
  int n_indices;

  bitsize = 0;
  fprintf_filtered (stream, "array (");

  n_indices = -1;
  if (show < 0)
    fprintf_filtered (stream, "...");
  else
    {
      if (ada_is_packed_array_type (type))
	type = ada_coerce_to_simple_array_type (type);
      if (ada_is_simple_array (type))
	{
	  struct type *range_desc_type =
	    ada_find_parallel_type (type, "___XA");
	  struct type *arr_type;

	  bitsize = 0;
	  if (range_desc_type == NULL)
	    {
	      for (arr_type = type; TYPE_CODE (arr_type) == TYPE_CODE_ARRAY;
		   arr_type = TYPE_TARGET_TYPE (arr_type))
		{
		  if (arr_type != type)
		    fprintf_filtered (stream, ", ");
		  print_range (TYPE_INDEX_TYPE (arr_type), stream);
		  if (TYPE_FIELD_BITSIZE (arr_type, 0) > 0)
		    bitsize = TYPE_FIELD_BITSIZE (arr_type, 0);
		}
	    }
	  else
	    {
	      int k;
	      n_indices = TYPE_NFIELDS (range_desc_type);
	      for (k = 0, arr_type = type;
		   k < n_indices;
		   k += 1, arr_type = TYPE_TARGET_TYPE (arr_type))
		{
		  if (k > 0)
		    fprintf_filtered (stream, ", ");
		  print_range_type_named (TYPE_FIELD_NAME
					  (range_desc_type, k), stream);
		  if (TYPE_FIELD_BITSIZE (arr_type, 0) > 0)
		    bitsize = TYPE_FIELD_BITSIZE (arr_type, 0);
		}
	    }
	}
      else
	{
	  int i, i0;
	  for (i = i0 = ada_array_arity (type); i > 0; i -= 1)
	    fprintf_filtered (stream, "%s<>", i == i0 ? "" : ", ");
	}
    }

  fprintf_filtered (stream, ") of ");
  wrap_here ("");
  ada_print_type (ada_array_element_type (type, n_indices), "", stream,
		  show == 0 ? 0 : show - 1, level + 1);
  if (bitsize > 0)
    fprintf_filtered (stream, " <packed: %d-bit elements>", bitsize);
}