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
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ isprint (char) ; 
 char* quote (char) ; 

__attribute__((used)) static void print(Buffer *b, char c) {
    char *q = quote(c);
    if (q) {
        buf_printf(b, "%s", q);
    } else if (isprint(c)) {
        buf_printf(b, "%c", c);
    } else {
        buf_printf(b, "\\x%02x", c);
    }
}