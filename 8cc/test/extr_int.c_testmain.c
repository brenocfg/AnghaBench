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
 int /*<<< orphan*/  expectl (int,int) ; 
 int /*<<< orphan*/  expects (int,short) ; 
 int /*<<< orphan*/  print (char*) ; 

void testmain() {
    print("long");

    short a = 10;
    short int b = 15;
    expects(25, a + b);
    expects(20, a + 10);

    long x = 67;
    long int y = 69;
    expectl(67, x);
    expectl(136, x + y);
    expectl(10L, 10L);
    expectl(4294967295L, 4294967295);
    expectl(1152921504606846976, 1152921504606846976);
    expectl(1152921504606846977, 1152921504606846976 + 1);
}