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
typedef  int /*<<< orphan*/  va_list ;
struct ui_out {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream; scalar_t__ suppress_output; } ;
typedef  TYPE_1__ cli_out_data ;

/* Variables and functions */
 TYPE_1__* ui_out_data (struct ui_out*) ; 
 int ui_out_get_verblvl (struct ui_out*) ; 
 int /*<<< orphan*/  vfprintf_unfiltered (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
cli_message (struct ui_out *uiout, int verbosity,
	     const char *format, va_list args)
{
  cli_out_data *data = ui_out_data (uiout);
  if (data->suppress_output)
    return;
  if (ui_out_get_verblvl (uiout) >= verbosity)
    vfprintf_unfiltered (data->stream, format, args);
}