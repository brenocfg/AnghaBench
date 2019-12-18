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
 int readc () ; 
 int /*<<< orphan*/  unreadc (int) ; 

__attribute__((used)) static void skip_line() {
    for (;;) {
        int c = readc();
        if (c == EOF)
            return;
        if (c == '\n') {
            unreadc(c);
            return;
        }
    }
}