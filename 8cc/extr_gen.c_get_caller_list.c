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
 char* buf_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  functions ; 
 int /*<<< orphan*/ * make_buffer () ; 
 int /*<<< orphan*/  vec_get (int /*<<< orphan*/ ,int) ; 
 int vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *get_caller_list() {
    Buffer *b = make_buffer();
    for (int i = 0; i < vec_len(functions); i++) {
        if (i > 0)
            buf_printf(b, " -> ");
        buf_printf(b, "%s", vec_get(functions, i));
    }
    buf_write(b, '\0');
    return buf_body(b);
}