#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ui_out {int dummy; } ;
struct TYPE_3__ {int suppress_output; } ;
typedef  TYPE_1__ cli_out_data ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 TYPE_1__* ui_out_data (struct ui_out*) ; 

void
cli_table_begin (struct ui_out *uiout, int nbrofcols,
		 int nr_rows,
		 const char *tblid)
{
  cli_out_data *data = ui_out_data (uiout);
  if (nr_rows == 0)
    data->suppress_output = 1;
  else
    /* Only the table suppresses the output and, fortunately, a table
       is not a recursive data structure. */
    gdb_assert (data->suppress_output == 0);
}