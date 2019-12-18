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
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  VERBOSE ; 
 void* _stddbg ; 
 int /*<<< orphan*/  _stderr ; 
 void* _stdout ; 
 int /*<<< orphan*/  debug_level ; 
 int print_message_debug_level ; 
 int /*<<< orphan*/  stderr ; 
 void* stdout ; 

void init_debug()
{
	debug_level = VERBOSE;
	debug_level = INFO;
	print_message_debug_level = false;

	_stdout = stdout;
	_stddbg = stdout;
	_stderr = stderr;
}