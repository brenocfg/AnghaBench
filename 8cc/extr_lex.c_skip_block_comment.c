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
typedef  int /*<<< orphan*/  Pos ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  errorp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_pos (int) ; 
 int readc () ; 

__attribute__((used)) static void skip_block_comment() {
    Pos p = get_pos(-2);
    bool maybe_end = false;
    for (;;) {
        int c = readc();
        if (c == EOF)
            errorp(p, "premature end of block comment");
        if (c == '/' && maybe_end)
            return;
        maybe_end = (c == '*');
    }
}