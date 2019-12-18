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
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert_string (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * make_buffer () ; 

__attribute__((used)) static void test_buf() {
    Buffer *b = make_buffer();
    buf_write(b, 'a');
    buf_write(b, 'b');
    buf_write(b, '\0');
    assert_string("ab", buf_body(b));

    Buffer *b2 = make_buffer();
    buf_write(b2, '.');
    buf_printf(b2, "%s", "0123456789");
    assert_string(".0123456789", buf_body(b2));
}