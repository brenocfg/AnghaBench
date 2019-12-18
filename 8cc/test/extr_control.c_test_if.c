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
 int /*<<< orphan*/  expect (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_if1 () ; 
 int /*<<< orphan*/  test_if10 () ; 
 int /*<<< orphan*/  test_if11 () ; 
 int /*<<< orphan*/  test_if2 () ; 
 int /*<<< orphan*/  test_if3 () ; 
 int /*<<< orphan*/  test_if4 () ; 
 int /*<<< orphan*/  test_if5 () ; 
 int /*<<< orphan*/  test_if6 () ; 
 int /*<<< orphan*/  test_if7 () ; 
 int /*<<< orphan*/  test_if8 () ; 
 int /*<<< orphan*/  test_if9 () ; 

__attribute__((used)) static void test_if() {
    expect('a', test_if1());
    expect('b', test_if2());
    expect('c', test_if3());
    expect('d', test_if4());
    expect('e', test_if5());
    expect('f', test_if6());
    expect('g', test_if7());
    expect('h', test_if8());
    expect('i', test_if9());
    expect('j', test_if10());
    expect('k', test_if11());
}