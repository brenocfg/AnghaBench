#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ui_stream {int /*<<< orphan*/  stream; } ;
struct cleanup {int dummy; } ;
struct breakpoint {int type; char* dll_pathname; int /*<<< orphan*/  line_number; int /*<<< orphan*/ * source_file; TYPE_2__* loc; int /*<<< orphan*/  addr_string; scalar_t__ pending; int /*<<< orphan*/  number; int /*<<< orphan*/  exp; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  address; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* print_mention ) (struct breakpoint*) ;} ;

/* Variables and functions */
 scalar_t__ addressprint ; 
#define  bp_access_watchpoint 152 
#define  bp_breakpoint 151 
#define  bp_call_dummy 150 
#define  bp_catch_catch 149 
#define  bp_catch_exec 148 
#define  bp_catch_fork 147 
#define  bp_catch_load 146 
#define  bp_catch_throw 145 
#define  bp_catch_unload 144 
#define  bp_catch_vfork 143 
#define  bp_finish 142 
#define  bp_hardware_breakpoint 141 
#define  bp_hardware_watchpoint 140 
#define  bp_longjmp 139 
#define  bp_longjmp_resume 138 
#define  bp_none 137 
#define  bp_overlay_event 136 
#define  bp_read_watchpoint 135 
#define  bp_shlib_event 134 
#define  bp_step_resume 133 
#define  bp_thread_event 132 
#define  bp_through_sigtramp 131 
#define  bp_until 130 
#define  bp_watchpoint 129 
#define  bp_watchpoint_scope 128 
 int /*<<< orphan*/  breakpoint_create_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_breakpoint_hook (struct breakpoint*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct cleanup* make_cleanup_ui_out_stream_delete (struct ui_stream*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct breakpoint*) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_stream (int /*<<< orphan*/ ,char*,struct ui_stream*) ; 
 scalar_t__ ui_out_is_mi_like_p (int /*<<< orphan*/ ) ; 
 struct ui_stream* ui_out_stream_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 

__attribute__((used)) static void
mention (struct breakpoint *b)
{
  int say_where = 0;
  struct cleanup *old_chain, *ui_out_chain;
  struct ui_stream *stb;

  stb = ui_out_stream_new (uiout);
  old_chain = make_cleanup_ui_out_stream_delete (stb);

  /* FIXME: This is misplaced; mention() is called by things (like hitting a
     watchpoint) other than breakpoint creation.  It should be possible to
     clean this up and at the same time replace the random calls to
     breakpoint_changed with this hook, as has already been done for
     delete_breakpoint_hook and so on.  */
  if (create_breakpoint_hook)
    create_breakpoint_hook (b);
  breakpoint_create_event (b->number);

  if (b->ops != NULL && b->ops->print_mention != NULL)
    b->ops->print_mention (b);
  else
    switch (b->type)
      {
      case bp_none:
	printf_filtered ("(apparently deleted?) Eventpoint %d: ", b->number);
	break;
      case bp_watchpoint:
	ui_out_text (uiout, "Watchpoint ");
	ui_out_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "wpt");
	ui_out_field_int (uiout, "number", b->number);
	ui_out_text (uiout, ": ");
	print_expression (b->exp, stb->stream);
	ui_out_field_stream (uiout, "exp", stb);
	do_cleanups (ui_out_chain);
	break;
      case bp_hardware_watchpoint:
	ui_out_text (uiout, "Hardware watchpoint ");
	ui_out_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "wpt");
	ui_out_field_int (uiout, "number", b->number);
	ui_out_text (uiout, ": ");
	print_expression (b->exp, stb->stream);
	ui_out_field_stream (uiout, "exp", stb);
	do_cleanups (ui_out_chain);
	break;
      case bp_read_watchpoint:
	ui_out_text (uiout, "Hardware read watchpoint ");
	ui_out_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "hw-rwpt");
	ui_out_field_int (uiout, "number", b->number);
	ui_out_text (uiout, ": ");
	print_expression (b->exp, stb->stream);
	ui_out_field_stream (uiout, "exp", stb);
	do_cleanups (ui_out_chain);
	break;
      case bp_access_watchpoint:
	ui_out_text (uiout, "Hardware access (read/write) watchpoint ");
	ui_out_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "hw-awpt");
	ui_out_field_int (uiout, "number", b->number);
	ui_out_text (uiout, ": ");
	print_expression (b->exp, stb->stream);
	ui_out_field_stream (uiout, "exp", stb);
	do_cleanups (ui_out_chain);
	break;
      case bp_breakpoint:
	if (ui_out_is_mi_like_p (uiout))
	  {
	    say_where = 0;
	    break;
	  }
	printf_filtered ("Breakpoint %d", b->number);
	say_where = 1;
	break;
      case bp_hardware_breakpoint:
	if (ui_out_is_mi_like_p (uiout))
	  {
	    say_where = 0;
	    break;
	  }
	printf_filtered ("Hardware assisted breakpoint %d", b->number);
	say_where = 1;
	break;
      case bp_catch_load:
      case bp_catch_unload:
	printf_filtered ("Catchpoint %d (%s %s)",
			 b->number,
			 (b->type == bp_catch_load) ? "load" : "unload",
			 (b->dll_pathname != NULL) ? 
			 b->dll_pathname : "<any library>");
	break;
      case bp_catch_fork:
      case bp_catch_vfork:
	printf_filtered ("Catchpoint %d (%s)",
			 b->number,
			 (b->type == bp_catch_fork) ? "fork" : "vfork");
	break;
      case bp_catch_exec:
	printf_filtered ("Catchpoint %d (exec)",
			 b->number);
	break;
      case bp_catch_catch:
      case bp_catch_throw:
	printf_filtered ("Catchpoint %d (%s)",
			 b->number,
			 (b->type == bp_catch_catch) ? "catch" : "throw");
	break;

      case bp_until:
      case bp_finish:
      case bp_longjmp:
      case bp_longjmp_resume:
      case bp_step_resume:
      case bp_through_sigtramp:
      case bp_call_dummy:
      case bp_watchpoint_scope:
      case bp_shlib_event:
      case bp_thread_event:
      case bp_overlay_event:
	break;
      }

  if (say_where)
    {
      if (b->pending)
	{
	  printf_filtered (" (%s) pending.", b->addr_string);
	}
      else
	{
	  if (addressprint || b->source_file == NULL)
	    {
	      printf_filtered (" at ");
	      print_address_numeric (b->loc->address, 1, gdb_stdout);
	    }
	  if (b->source_file)
	    printf_filtered (": file %s, line %d.",
			     b->source_file, b->line_number);
	}
    }
  do_cleanups (old_chain);
  if (ui_out_is_mi_like_p (uiout))
    return;
  printf_filtered ("\n");
}