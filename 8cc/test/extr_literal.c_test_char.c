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

__attribute__((used)) static void test_char() {
    expect(65, 'A');
    expect(97, 'a');
    expect(7, '\a');
    expect(8, '\b');
    expect(12, '\f');
    expect(10, '\n');
    expect(13, '\r');
    expect(9, '\t');
    expect(11, '\v');
    expect(27, '\e');

    expect(0, '\0');
    expect(7, '\7');
    expect(15, '\17');
    expect(-99, '\235');

    expect(0, '\x0');
    expect(-1, '\xff');
    expect(15, '\xF');
    expect(18, '\x012');
}