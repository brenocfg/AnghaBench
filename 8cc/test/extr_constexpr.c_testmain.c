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
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p1 ; 
 int /*<<< orphan*/ * p2 ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/ * q1 ; 

void testmain() {
    print("constexpr");
    expect(1, *p1);
    expect(3, *q1);
    expect(7, p2[-1]);
}