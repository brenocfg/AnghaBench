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
typedef  enum type_code { ____Placeholder_type_code } type_code ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_ARRAY ; 
 int TYPE_CODE_FUNC ; 
 int TYPE_CODE_MEMBER ; 
 int TYPE_CODE_METHOD ; 
 int TYPE_CODE_PTR ; 
 int TYPE_CODE_REF ; 
 scalar_t__ TYPE_NAME (struct type*) ; 
 int /*<<< orphan*/  f_type_print_base (struct type*,struct ui_file*,int,int) ; 
 int /*<<< orphan*/  f_type_print_varspec_prefix (struct type*,struct ui_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_type_print_varspec_suffix (struct type*,struct ui_file*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int strlen (char*) ; 

void
f_print_type (struct type *type, char *varstring, struct ui_file *stream,
	      int show, int level)
{
  enum type_code code;
  int demangled_args;

  f_type_print_base (type, stream, show, level);
  code = TYPE_CODE (type);
  if ((varstring != NULL && *varstring != '\0')
      ||
  /* Need a space if going to print stars or brackets;
     but not if we will print just a type name.  */
      ((show > 0 || TYPE_NAME (type) == 0)
       &&
       (code == TYPE_CODE_PTR || code == TYPE_CODE_FUNC
	|| code == TYPE_CODE_METHOD
	|| code == TYPE_CODE_ARRAY
	|| code == TYPE_CODE_MEMBER
	|| code == TYPE_CODE_REF)))
    fputs_filtered (" ", stream);
  f_type_print_varspec_prefix (type, stream, show, 0);

  fputs_filtered (varstring, stream);

  /* For demangled function names, we have the arglist as part of the name,
     so don't print an additional pair of ()'s */

  demangled_args = varstring[strlen (varstring) - 1] == ')';
  f_type_print_varspec_suffix (type, stream, show, 0, demangled_args);
}