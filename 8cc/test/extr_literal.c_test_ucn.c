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
 int /*<<< orphan*/  expect (char,int) ; 
 int /*<<< orphan*/  expect_string (char*,char*) ; 

__attribute__((used)) static void test_ucn() {
    expect('$', L'\u0024');
    expect('$', L'\U00000024');
    expect_string("$", "\u0024");
    expect_string("$", "\U00000024");
    expect('X', L'X');
    expect('X', U'X');
    expect('X', u'X');
}