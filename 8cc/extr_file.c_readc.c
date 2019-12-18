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
 int /*<<< orphan*/  close_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  files ; 
 int get () ; 
 int /*<<< orphan*/  unreadc (int) ; 
 int vec_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_pop (int /*<<< orphan*/ ) ; 

int readc() {
    for (;;) {
        int c = get();
        if (c == EOF) {
            if (vec_len(files) == 1)
                return c;
            close_file(vec_pop(files));
            continue;
        }
        if (c != '\\')
            return c;
        int c2 = get();
        if (c2 == '\n')
            continue;
        unreadc(c2);
        return c;
    }
}