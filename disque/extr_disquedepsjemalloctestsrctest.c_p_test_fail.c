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
 int /*<<< orphan*/  malloc_cprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 int /*<<< orphan*/  test_status ; 
 int /*<<< orphan*/  test_status_fail ; 

void
p_test_fail(const char *prefix, const char *message)
{

	malloc_cprintf(NULL, NULL, "%s%s\n", prefix, message);
	test_status = test_status_fail;
}