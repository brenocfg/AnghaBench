#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
struct field {int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ la_language; } ;

/* Variables and functions */
 struct field* TYPE_FIELDS (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 scalar_t__ TYPE_VARARGS (struct type*) ; 
 int /*<<< orphan*/  c_print_type (int /*<<< orphan*/ ,char*,struct ui_file*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 scalar_t__ language_cplus ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
c_type_print_args (struct type *type, struct ui_file *stream)
{
  int i;
  struct field *args;

  fprintf_filtered (stream, "(");
  args = TYPE_FIELDS (type);
  if (args != NULL)
    {
      int i;

      /* FIXME drow/2002-05-31: Always skips the first argument,
	 should we be checking for static members?  */

      for (i = 1; i < TYPE_NFIELDS (type); i++)
	{
	  c_print_type (args[i].type, "", stream, -1, 0);
	  if (i != TYPE_NFIELDS (type))
	    {
	      fprintf_filtered (stream, ",");
	      wrap_here ("    ");
	    }
	}
      if (TYPE_VARARGS (type))
	fprintf_filtered (stream, "...");
      else if (i == 1
	       && (current_language->la_language == language_cplus))
	fprintf_filtered (stream, "void");
    }
  else if (current_language->la_language == language_cplus)
    {
      fprintf_filtered (stream, "void");
    }

  fprintf_filtered (stream, ")");
}