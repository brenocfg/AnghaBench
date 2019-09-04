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
typedef  int /*<<< orphan*/  FTPContext ;

/* Variables and functions */
 int ftp_getc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftp_get_line(FTPContext *s, char *line, int line_size)
{
    int ch;
    char *q = line;

    for (;;) {
        ch = ftp_getc(s);
        if (ch < 0) {
            return ch;
        }
        if (ch == '\n') {
            /* process line */
            if (q > line && q[-1] == '\r')
                q--;
            *q = '\0';
            return 0;
        } else {
            if ((q - line) < line_size - 1)
                *q++ = ch;
        }
    }
}