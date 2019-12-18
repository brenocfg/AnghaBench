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
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,int) ; 

__attribute__((used)) static void test_comma() {
    expect(3, (1, 3));
    expectf(7.0, (1, 3, 5, 7.0));
}