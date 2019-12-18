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

__attribute__((used)) static void defined() {
    int a = 0;
#if defined ZERO
    a = 1;
#endif
    expect(1, a);
#if defined(ZERO)
    a = 2;
#endif
    expect(2, a);
#if defined(NO_SUCH_MACRO)
    a = 3;
#else
    a = 4;
#endif
    expect(4, a);
}