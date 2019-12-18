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

__attribute__((used)) static void many_ints(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9) {
    expect(1, v1); expect(2, v2); expect(3, v3); expect(4, v4);
    expect(5, v5); expect(6, v6); expect(7, v7); expect(8, v8);
    expect(9, v9);
}