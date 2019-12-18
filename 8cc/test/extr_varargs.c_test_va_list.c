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
 int /*<<< orphan*/  expect_string (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmt (char*,...) ; 

__attribute__((used)) static void test_va_list() {
    expect_string("", fmt(""));
    expect_string("3", fmt("%d", 3));
    expect_string("3,1.0,6,2.0,abc", fmt("%d,%.1f,%d,%.1f,%s", 3, 1.0, 6, 2.0, "abc"));
}