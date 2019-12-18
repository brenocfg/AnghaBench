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
typedef  enum tag { ____Placeholder_tag } tag ;

/* Variables and functions */
 int /*<<< orphan*/  expect (int,int) ; 
 int g1 ; 
 int g3 ; 
 int /*<<< orphan*/  print (char*) ; 

void testmain() {
    print("enum");

    expect(0, g1);
    expect(2, g3);

    enum { x } v;
    expect(0, x);

    enum { y };
    expect(0, y);

    enum tag { z };
    enum tag a = z;
    expect(0, z);
    expect(0, a);
}