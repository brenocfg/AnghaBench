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
typedef  int /*<<< orphan*/  thread_name ;

/* Variables and functions */
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  mallctl (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int) ; 
 int /*<<< orphan*/  mallctl_thread_name_get_impl (char const*,char const*,int) ; 

__attribute__((used)) static void
mallctl_thread_name_set_impl(const char *thread_name, const char *func,
    int line)
{

	assert_d_eq(mallctl("thread.prof.name", NULL, NULL, &thread_name,
	    sizeof(thread_name)), 0,
	    "%s():%d: Unexpected mallctl failure reading thread.prof.name",
	    func, line);
	mallctl_thread_name_get_impl(thread_name, func, line);
}