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
 int fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int getCursorPosition () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 

__attribute__((used)) static int getColumns(void) {
    int start, cols;

    /* Get the initial position so we can restore it later. */
    start = getCursorPosition();
    if (start == -1) goto failed;

    /* Go to right margin and get position. */
    if (fwrite("\x1b[999C", 1, 6, stdout) != 6) goto failed;
    cols = getCursorPosition();
    if (cols == -1) goto failed;

    /* Restore position. */
    if (cols > start) {
        char seq[32];
        snprintf(seq,32,"\x1b[%dD",cols-start);
        if (fwrite(seq, 1, strlen(seq), stdout) == -1) {
            /* Can't recover... */
        }
    }
    return cols;

failed:
    return 80;
}