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
 int /*<<< orphan*/  booltest1 (int) ; 
 int /*<<< orphan*/  booltest2 (int) ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_bool() {
    expect(0, booltest1(256));
    expect(1, booltest1(257));
    expect(1, booltest2(512));
    expect(1, booltest2(513));
}