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
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_VOID ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  ada_print_type (int /*<<< orphan*/ ,char*,struct ui_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
print_func_type (struct type *type, struct ui_file *stream, char *name)
{
  int i, len = TYPE_NFIELDS (type);

  if (TYPE_CODE (TYPE_TARGET_TYPE (type)) == TYPE_CODE_VOID)
    fprintf_filtered (stream, "procedure");
  else
    fprintf_filtered (stream, "function");

  if (name != NULL && name[0] != '\0')
    fprintf_filtered (stream, " %s", name);

  if (len > 0)
    {
      fprintf_filtered (stream, " (");
      for (i = 0; i < len; i += 1)
	{
	  if (i > 0)
	    {
	      fputs_filtered ("; ", stream);
	      wrap_here ("    ");
	    }
	  fprintf_filtered (stream, "a%d: ", i + 1);
	  ada_print_type (TYPE_FIELD_TYPE (type, i), "", stream, -1, 0);
	}
      fprintf_filtered (stream, ")");
    }

  if (TYPE_CODE (TYPE_TARGET_TYPE (type)) != TYPE_CODE_VOID)
    {
      fprintf_filtered (stream, " return ");
      ada_print_type (TYPE_TARGET_TYPE (type), "", stream, 0, 0);
    }
}