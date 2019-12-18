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
struct TYPE_3__ {scalar_t__ suppress_output; } ;
typedef  TYPE_1__ cli_out_data ;

/* Variables and functions */
 TYPE_1__* ui_out_data (struct ui_out*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

void
cli_wrap_hint (struct ui_out *uiout, char *identstring)
{
  cli_out_data *data = ui_out_data (uiout);
  if (data->suppress_output)
    return;
  wrap_here (identstring);
}