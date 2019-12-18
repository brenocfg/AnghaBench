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
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_FUNC ; 
 int TYPE_CODE_METHOD ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  pascal_type_print_base (struct type*,struct ui_file*,int,int) ; 
 int /*<<< orphan*/  pascal_type_print_varspec_prefix (struct type*,struct ui_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pascal_type_print_varspec_suffix (struct type*,struct ui_file*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

void
pascal_print_type (struct type *type, char *varstring, struct ui_file *stream,
		   int show, int level)
{
  enum type_code code;
  int demangled_args;

  code = TYPE_CODE (type);

  if (show > 0)
    CHECK_TYPEDEF (type);

  if ((code == TYPE_CODE_FUNC ||
       code == TYPE_CODE_METHOD))
    {
      pascal_type_print_varspec_prefix (type, stream, show, 0);
    }
  /* first the name */
  fputs_filtered (varstring, stream);

  if ((varstring != NULL && *varstring != '\0') &&
      !(code == TYPE_CODE_FUNC ||
	code == TYPE_CODE_METHOD))
    {
      fputs_filtered (" : ", stream);
    }

  if (!(code == TYPE_CODE_FUNC ||
	code == TYPE_CODE_METHOD))
    {
      pascal_type_print_varspec_prefix (type, stream, show, 0);
    }

  pascal_type_print_base (type, stream, show, level);
  /* For demangled function names, we have the arglist as part of the name,
     so don't print an additional pair of ()'s */

  demangled_args = varstring ? strchr (varstring, '(') != NULL : 0;
  pascal_type_print_varspec_suffix (type, stream, show, 0, demangled_args);

}