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
struct TYPE_3__ {int /*<<< orphan*/  stream; scalar_t__ suppress_output; } ;
typedef  TYPE_1__ cli_out_data ;

/* Variables and functions */
 int /*<<< orphan*/  print_spaces_filtered (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ui_out_data (struct ui_out*) ; 

void
cli_spaces (struct ui_out *uiout, int numspaces)
{
  cli_out_data *data = ui_out_data (uiout);
  if (data->suppress_output)
    return;
  print_spaces_filtered (numspaces, data->stream);
}