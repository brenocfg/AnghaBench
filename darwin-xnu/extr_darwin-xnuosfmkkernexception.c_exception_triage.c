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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_exception_data_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  exception_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  exception_triage_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
exception_triage(
	exception_type_t	exception,
	mach_exception_data_t	code,
	mach_msg_type_number_t  codeCnt)
{
	thread_t thread = current_thread();
	return exception_triage_thread(exception, code, codeCnt, thread);
}