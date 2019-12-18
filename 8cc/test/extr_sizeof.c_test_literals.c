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

__attribute__((used)) static void test_literals() {
    expect(4, sizeof 1);
    expect(4, sizeof('a'));
    expect(4, sizeof(1.0f));
    expect(8, sizeof 1L);
    expect(8, sizeof 1.0);
    expect(8, sizeof(1.0));
}