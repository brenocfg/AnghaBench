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
 scalar_t__ TYPE_CODE_PTR ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_FLAGS (struct type*) ; 
 int TYPE_FLAG_STUB ; 
 int TYPE_NFIELDS (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 struct type* ada_find_parallel_type (struct type*,char*) ; 
 struct type* ada_variant_discrim_type (struct type*,struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  print_choices (struct type*,int,struct ui_file*,struct type*) ; 
 scalar_t__ print_record_field_types (struct type*,struct type*,struct ui_file*,int,int) ; 

__attribute__((used)) static void
print_variant_clauses (struct type *type, int field_num,
		       struct type *outer_type, struct ui_file *stream,
		       int show, int level)
{
  int i;
  struct type *var_type;
  struct type *discr_type;

  var_type = TYPE_FIELD_TYPE (type, field_num);
  discr_type = ada_variant_discrim_type (var_type, outer_type);

  if (TYPE_CODE (var_type) == TYPE_CODE_PTR)
    {
      var_type = TYPE_TARGET_TYPE (var_type);
      if (TYPE_FLAGS (var_type) & TYPE_FLAG_STUB)
	{
	  var_type = ada_find_parallel_type (var_type, "___XVU");
	  if (var_type == NULL)
	    return;
	}
    }

  for (i = 0; i < TYPE_NFIELDS (var_type); i += 1)
    {
      fprintf_filtered (stream, "\n%*swhen ", level + 4, "");
      print_choices (var_type, i, stream, discr_type);
      fprintf_filtered (stream, " =>");
      if (print_record_field_types (TYPE_FIELD_TYPE (var_type, i),
				    outer_type, stream, show, level + 4) <= 0)
	fprintf_filtered (stream, " null;");
    }
}