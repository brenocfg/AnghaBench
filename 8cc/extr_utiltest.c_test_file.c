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
 int /*<<< orphan*/  assert_int (char,scalar_t__) ; 
 int /*<<< orphan*/  assert_true (int) ; 
 int /*<<< orphan*/  make_file_string (char*) ; 
 scalar_t__ readc () ; 
 int /*<<< orphan*/  stream_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unreadc (char) ; 

__attribute__((used)) static void test_file() {
    stream_push(make_file_string("abc"));
    assert_int('a', readc());
    assert_int('b', readc());
    unreadc('b');
    unreadc('a');
    assert_int('a', readc());
    assert_int('b', readc());
    assert_int('c', readc());
    assert_int('\n', readc());
    unreadc('\n');
    assert_int('\n', readc());
    assert_true(readc() < 0);
}