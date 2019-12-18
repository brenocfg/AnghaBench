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
struct jpeg_error_mgr {int last_jpeg_message; scalar_t__ last_addon_message; scalar_t__ first_addon_message; int /*<<< orphan*/ * addon_message_table; int /*<<< orphan*/  jpeg_message_table; scalar_t__ msg_code; scalar_t__ num_warnings; scalar_t__ trace_level; int /*<<< orphan*/  reset_error_mgr; int /*<<< orphan*/  format_message; int /*<<< orphan*/  output_message; int /*<<< orphan*/  emit_message; int /*<<< orphan*/  error_exit; } ;

/* Variables and functions */
 scalar_t__ JMSG_LASTMSGCODE ; 
 int /*<<< orphan*/  emit_message ; 
 int /*<<< orphan*/  error_exit ; 
 int /*<<< orphan*/  format_message ; 
 int /*<<< orphan*/  jpeg_std_message_table ; 
 int /*<<< orphan*/  output_message ; 
 int /*<<< orphan*/  reset_error_mgr ; 

struct jpeg_error_mgr *
jpeg_std_error (struct jpeg_error_mgr * err)
{
  err->error_exit = error_exit;
  err->emit_message = emit_message;
  err->output_message = output_message;
  err->format_message = format_message;
  err->reset_error_mgr = reset_error_mgr;

  err->trace_level = 0;		/* default = no tracing */
  err->num_warnings = 0;	/* no warnings emitted yet */
  err->msg_code = 0;		/* may be useful as a flag for "no error" */

  /* Initialize message table pointers */
  err->jpeg_message_table = jpeg_std_message_table;
  err->last_jpeg_message = (int) JMSG_LASTMSGCODE - 1;

  err->addon_message_table = NULL;
  err->first_addon_message = 0;	/* for safety */
  err->last_addon_message = 0;

  return err;
}