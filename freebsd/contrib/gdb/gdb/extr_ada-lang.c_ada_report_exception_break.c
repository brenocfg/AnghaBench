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
struct breakpoint {int dummy; } ;

/* Variables and functions */

void
ada_report_exception_break (struct breakpoint *b)
{
  /* FIXME: break_on_exception should be defined in breakpoint.h */
  /*  if (b->break_on_exception == 1)
     {
     /* Assume that cond has 16 elements, the 15th
   being the exception *//*
   if (b->cond && b->cond->nelts == 16)
   {
   ui_out_text (uiout, "on ");
   ui_out_field_string (uiout, "exception",
   SYMBOL_NAME (b->cond->elts[14].symbol));
   }
   else
   ui_out_text (uiout, "on all exceptions");
   }
   else if (b->break_on_exception == 2)
   ui_out_text (uiout, "on unhandled exception");
   else if (b->break_on_exception == 3)
   ui_out_text (uiout, "on assert failure");
   #else
   if (b->break_on_exception == 1)
   { */
  /* Assume that cond has 16 elements, the 15th
   being the exception *//*
   if (b->cond && b->cond->nelts == 16)
   {
   fputs_filtered ("on ", gdb_stdout);
   fputs_filtered (SYMBOL_NAME
   (b->cond->elts[14].symbol), gdb_stdout);
   }
   else
   fputs_filtered ("on all exceptions", gdb_stdout);
   }
   else if (b->break_on_exception == 2)
   fputs_filtered ("on unhandled exception", gdb_stdout);
   else if (b->break_on_exception == 3)
   fputs_filtered ("on assert failure", gdb_stdout);
 */
}