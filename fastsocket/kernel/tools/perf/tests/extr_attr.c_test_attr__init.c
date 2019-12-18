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
 int /*<<< orphan*/  ENV ; 
 int /*<<< orphan*/ * dir ; 
 int /*<<< orphan*/ * getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_attr__enabled ; 

void test_attr__init(void)
{
	dir = getenv(ENV);
	test_attr__enabled = (dir != NULL);
}