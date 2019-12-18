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
struct tracepoint_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_event_system (char*,struct tracepoint_path*) ; 
 char* get_tracing_file (char*) ; 
 int /*<<< orphan*/  put_tracing_file (char*) ; 

__attribute__((used)) static void read_ftrace_files(struct tracepoint_path *tps)
{
	char *path;

	path = get_tracing_file("events/ftrace");

	copy_event_system(path, tps);

	put_tracing_file(path);
}