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
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  TYPE_FIELD_NAME (struct type*,int) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_FLAGS (struct type*) ; 
 int TYPE_FLAG_STUB ; 
 int TYPE_NFIELDS (struct type*) ; 
 scalar_t__ ada_is_ignored_field (struct type*,int) ; 
 scalar_t__ ada_is_parent_field (struct type*,int) ; 
 scalar_t__ ada_is_variant_part (struct type*,int) ; 
 scalar_t__ ada_is_wrapper_field (struct type*,int) ; 
 int /*<<< orphan*/  ada_print_type (struct type*,int /*<<< orphan*/ ,struct ui_file*,int,int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  print_variant_part (struct type*,int,struct type*,struct ui_file*,int,int) ; 

__attribute__((used)) static int
print_record_field_types (struct type *type, struct type *outer_type,
			  struct ui_file *stream, int show, int level)
{
  int len, i, flds;

  flds = 0;
  len = TYPE_NFIELDS (type);

  if (len == 0 && (TYPE_FLAGS (type) & TYPE_FLAG_STUB) != 0)
    return -1;

  for (i = 0; i < len; i += 1)
    {
      QUIT;

      if (ada_is_parent_field (type, i) || ada_is_ignored_field (type, i))
	;
      else if (ada_is_wrapper_field (type, i))
	flds += print_record_field_types (TYPE_FIELD_TYPE (type, i), type,
					  stream, show, level);
      else if (ada_is_variant_part (type, i))
	{
	  print_variant_part (type, i, outer_type, stream, show, level);
	  flds = 1;
	}
      else
	{
	  flds += 1;
	  fprintf_filtered (stream, "\n%*s", level + 4, "");
	  ada_print_type (TYPE_FIELD_TYPE (type, i),
			  TYPE_FIELD_NAME (type, i),
			  stream, show - 1, level + 4);
	  fprintf_filtered (stream, ";");
	}
    }

  return flds;
}