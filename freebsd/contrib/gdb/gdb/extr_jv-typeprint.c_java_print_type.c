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
 int /*<<< orphan*/  c_type_print_varspec_suffix (struct type*,struct ui_file*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  java_type_print_base (struct type*,struct ui_file*,int,int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

void
java_print_type (struct type *type, char *varstring, struct ui_file *stream,
		 int show, int level)
{
  int demangled_args;

  java_type_print_base (type, stream, show, level);

  if (varstring != NULL && *varstring != '\0')
    {
      fputs_filtered (" ", stream);
      fputs_filtered (varstring, stream);
    }

  /* For demangled function names, we have the arglist as part of the name,
     so don't print an additional pair of ()'s */

  demangled_args = strchr (varstring, '(') != NULL;
  c_type_print_varspec_suffix (type, stream, show, 0, demangled_args);
}