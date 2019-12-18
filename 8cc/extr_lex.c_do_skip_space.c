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
 int EOF ; 
 scalar_t__ iswhitespace (int) ; 
 scalar_t__ next (char) ; 
 int readc () ; 
 int /*<<< orphan*/  skip_block_comment () ; 
 int /*<<< orphan*/  skip_line () ; 
 int /*<<< orphan*/  unreadc (int) ; 

__attribute__((used)) static bool do_skip_space() {
    int c = readc();
    if (c == EOF)
        return false;
    if (iswhitespace(c))
        return true;
    if (c == '/') {
        if (next('*')) {
            skip_block_comment();
            return true;
        }
        if (next('/')) {
            skip_line();
            return true;
        }
    }
    unreadc(c);
    return false;
}