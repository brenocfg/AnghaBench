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
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  pascal_print_type (int /*<<< orphan*/ ,char*,struct ui_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
pascal_print_func_args (struct type *type, struct ui_file *stream)
{
  int i, len = TYPE_NFIELDS (type);
  if (len)
    {
      fprintf_filtered (stream, "(");
    }
  for (i = 0; i < len; i++)
    {
      if (i > 0)
	{
	  fputs_filtered (", ", stream);
	  wrap_here ("    ");
	}
      /*  can we find if it is a var parameter ??
         if ( TYPE_FIELD(type, i) == )
         {
         fprintf_filtered (stream, "var ");
         } */
      pascal_print_type (TYPE_FIELD_TYPE (type, i), ""	/* TYPE_FIELD_NAME seems invalid ! */
			 ,stream, -1, 0);
    }
  if (len)
    {
      fprintf_filtered (stream, ")");
    }
}