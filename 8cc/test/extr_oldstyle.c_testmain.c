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
 int /*<<< orphan*/  no_declaration () ; 
 int /*<<< orphan*/  oldstyle1 (int,int) ; 
 int /*<<< orphan*/  oldstyle2 () ; 
 int /*<<< orphan*/  oldstyle3 (int) ; 
 int /*<<< orphan*/  oldstyle4 (int,double) ; 
 int /*<<< orphan*/  print (char*) ; 

void testmain() {
    print("K&R");
    expect(3, no_declaration());
    expect(7, oldstyle1(3, 4));
    expect(4, oldstyle2());
    expect(5, oldstyle3(5));
    expect(9, oldstyle4(5, 4.0));
}