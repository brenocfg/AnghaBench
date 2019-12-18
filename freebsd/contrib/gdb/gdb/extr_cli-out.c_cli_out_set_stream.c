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
struct ui_file {int dummy; } ;
struct TYPE_3__ {struct ui_file* stream; } ;
typedef  TYPE_1__ cli_out_data ;

/* Variables and functions */
 TYPE_1__* ui_out_data (struct ui_out*) ; 

struct ui_file *
cli_out_set_stream (struct ui_out *uiout, struct ui_file *stream)
{
  cli_out_data *data = ui_out_data (uiout);
  struct ui_file *old = data->stream;
  data->stream = stream;
  return old;
}