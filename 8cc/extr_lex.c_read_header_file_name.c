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
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int EOF ; 
 char* buf_body (int /*<<< orphan*/ *) ; 
 scalar_t__ buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  buffer_empty () ; 
 int /*<<< orphan*/  errorp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_buffer () ; 
 scalar_t__ next (char) ; 
 int readc () ; 
 int /*<<< orphan*/  skip_space () ; 

char *read_header_file_name(bool *std) {
    if (!buffer_empty())
        return NULL;
    skip_space();
    Pos p = get_pos(0);
    char close;
    if (next('"')) {
        *std = false;
        close = '"';
    } else if (next('<')) {
        *std = true;
        close = '>';
    } else {
        return NULL;
    }
    Buffer *b = make_buffer();
    while (!next(close)) {
        int c = readc();
        if (c == EOF || c == '\n')
            errorp(p, "premature end of header name");
        buf_write(b, c);
    }
    if (buf_len(b) == 0)
        errorp(p, "header name should not be empty");
    buf_write(b, '\0');
    return buf_body(b);
}