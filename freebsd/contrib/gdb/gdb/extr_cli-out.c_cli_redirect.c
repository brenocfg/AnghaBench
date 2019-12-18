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
struct ui_out_data {struct ui_file* original_stream; struct ui_file* stream; } ;
struct ui_out {int dummy; } ;
struct ui_file {int dummy; } ;

/* Variables and functions */
 struct ui_out_data* ui_out_data (struct ui_out*) ; 

int
cli_redirect (struct ui_out *uiout, struct ui_file *outstream)
{
  struct ui_out_data *data = ui_out_data (uiout);
  if (outstream != NULL)
    {
      data->original_stream = data->stream;
      data->stream = outstream;
    }
  else if (data->original_stream != NULL)
    {
      data->stream = data->original_stream;
      data->original_stream = NULL;
    }

  return 0;
}