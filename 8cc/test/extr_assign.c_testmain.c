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
 int /*<<< orphan*/  expect (int,char) ; 
 int /*<<< orphan*/  print (char*) ; 

void testmain() {
    print("compound assignment");

    int a = 0;
    a += 5;
    expect(5, a);
    a -= 2;
    expect(3, a);
    a *= 10;
    expect(30, a);
    a /= 2;
    expect(15, a);
    a %= 6;
    expect(3, a);

    a = 14;
    a &= 7;
    expect(6, a);
    a |= 8;
    expect(14, a);
    a ^= 3;
    expect(13, a);
    a <<= 2;
    expect(52, a);
    a >>= 2;
    expect(13, a);

    char b = 0;
    b += 5;
    expect(5, b);
    b -= 2;
    expect(3, b);
    b *= 10;
    expect(30, b);
    b /= 2;
    expect(15, b);
    b %= 6;
    expect(3, b);

    b = 14;
    b &= 7;
    expect(6, b);
    b |= 8;
    expect(14, b);
    b ^= 3;
    expect(13, b);
    b <<= 2;
    expect(52, b);
    b >>= 2;
    expect(13, b);
}