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

/* Variables and functions */
 int /*<<< orphan*/  emscripten_trace_configure_for_test () ; 
 int /*<<< orphan*/  emscripten_trace_enter_context (char*) ; 
 int /*<<< orphan*/  emscripten_trace_exit_context () ; 
 int /*<<< orphan*/  emscripten_trace_log_message (char*,char*) ; 
 int /*<<< orphan*/  emscripten_trace_record_frame_end () ; 
 int /*<<< orphan*/  emscripten_trace_record_frame_start () ; 

int main(int argc, const char* argv[]) {

  emscripten_trace_configure_for_test();

  emscripten_trace_enter_context("Application Startup");
  emscripten_trace_log_message("Application", "starting up");
  emscripten_trace_exit_context();

  emscripten_trace_record_frame_start();
  emscripten_trace_record_frame_end();

  return 0;
}