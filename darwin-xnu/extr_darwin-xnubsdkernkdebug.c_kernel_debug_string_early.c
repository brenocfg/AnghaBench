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
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_DEBUG_EARLY (int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_INFO_STRING ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int /*<<< orphan*/ ) ; 

void
kernel_debug_string_early(const char *message)
{
	uintptr_t arg[4] = {0, 0, 0, 0};

	/* Stuff the message string in the args and log it. */
	strncpy((char *)arg, message, MIN(sizeof(arg), strlen(message)));
	KERNEL_DEBUG_EARLY(
		TRACE_INFO_STRING,
		arg[0], arg[1], arg[2], arg[3]);
}