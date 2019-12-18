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
 int TYPE_FLAGS (struct type*) ; 
 int TYPE_FLAG_STUB ; 
 struct type* ada_find_parallel_type (struct type*,char*) ; 
 scalar_t__ ada_is_tagged_type (struct type*) ; 
 struct type* ada_parent_type (struct type*) ; 
 int /*<<< orphan*/ * ada_type_name (struct type*) ; 
 int /*<<< orphan*/  demangled_type_name (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 scalar_t__ print_record_field_types (struct type*,struct type*,struct ui_file*,int,int) ; 

__attribute__((used)) static void
print_record_type (struct type *type0, struct ui_file *stream, int show,
		   int level)
{
  struct type *parent_type;
  struct type *type;

  type = type0;
  if (TYPE_FLAGS (type) & TYPE_FLAG_STUB)
    {
      struct type *type1 = ada_find_parallel_type (type, "___XVE");
      if (type1 != NULL)
	type = type1;
    }

  parent_type = ada_parent_type (type);
  if (ada_type_name (parent_type) != NULL)
    fprintf_filtered (stream, "new %s with ",
		      demangled_type_name (parent_type));
  else if (parent_type == NULL && ada_is_tagged_type (type))
    fprintf_filtered (stream, "tagged ");

  fprintf_filtered (stream, "record");

  if (show < 0)
    fprintf_filtered (stream, " ... end record");
  else
    {
      int flds;

      flds = 0;
      if (parent_type != NULL && ada_type_name (parent_type) == NULL)
	flds += print_record_field_types (parent_type, parent_type,
					  stream, show, level);
      flds += print_record_field_types (type, type, stream, show, level);

      if (flds > 0)
	fprintf_filtered (stream, "\n%*send record", level, "");
      else if (flds < 0)
	fprintf_filtered (stream, " <incomplete type> end record");
      else
	fprintf_filtered (stream, " null; end record");
    }
}