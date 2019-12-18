#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  magic; int /*<<< orphan*/  poll_quit; int /*<<< orphan*/  error; int /*<<< orphan*/  evprintf_filtered; int /*<<< orphan*/  vprintf_filtered; int /*<<< orphan*/  printf_filtered; int /*<<< orphan*/  flush_stderr; int /*<<< orphan*/  write_stderr; int /*<<< orphan*/  flush_stdout; int /*<<< orphan*/  write_stdout; int /*<<< orphan*/  (* init ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CALLBACK_MAGIC ; 
 int callbacks_initialized ; 
 TYPE_1__ default_callback ; 
 TYPE_1__ gdb_callback ; 
 int /*<<< orphan*/  gdb_os_error ; 
 int /*<<< orphan*/  gdb_os_evprintf_filtered ; 
 int /*<<< orphan*/  gdb_os_flush_stderr ; 
 int /*<<< orphan*/  gdb_os_flush_stdout ; 
 int /*<<< orphan*/  gdb_os_poll_quit ; 
 int /*<<< orphan*/  gdb_os_printf_filtered ; 
 int /*<<< orphan*/  gdb_os_vprintf_filtered ; 
 int /*<<< orphan*/  gdb_os_write_stderr ; 
 int /*<<< orphan*/  gdb_os_write_stdout ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
init_callbacks (void)
{
  if (!callbacks_initialized)
    {
      gdb_callback = default_callback;
      gdb_callback.init (&gdb_callback);
      gdb_callback.write_stdout = gdb_os_write_stdout;
      gdb_callback.flush_stdout = gdb_os_flush_stdout;
      gdb_callback.write_stderr = gdb_os_write_stderr;
      gdb_callback.flush_stderr = gdb_os_flush_stderr;
      gdb_callback.printf_filtered = gdb_os_printf_filtered;
      gdb_callback.vprintf_filtered = gdb_os_vprintf_filtered;
      gdb_callback.evprintf_filtered = gdb_os_evprintf_filtered;
      gdb_callback.error = gdb_os_error;
      gdb_callback.poll_quit = gdb_os_poll_quit;
      gdb_callback.magic = HOST_CALLBACK_MAGIC;
      callbacks_initialized = 1;
    }
}