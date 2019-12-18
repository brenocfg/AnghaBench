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
struct perf_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __print_result (int /*<<< orphan*/ *,struct perf_session*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ alloc_flag ; 
 int /*<<< orphan*/  alloc_lines ; 
 scalar_t__ caller_flag ; 
 int /*<<< orphan*/  caller_lines ; 
 int /*<<< orphan*/  print_summary () ; 
 int /*<<< orphan*/  root_alloc_sorted ; 
 int /*<<< orphan*/  root_caller_sorted ; 

__attribute__((used)) static void print_result(struct perf_session *session)
{
	if (caller_flag)
		__print_result(&root_caller_sorted, session, caller_lines, 1);
	if (alloc_flag)
		__print_result(&root_alloc_sorted, session, alloc_lines, 0);
	print_summary();
}