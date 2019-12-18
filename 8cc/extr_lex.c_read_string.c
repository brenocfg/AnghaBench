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
typedef  int /*<<< orphan*/  Token ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  buf_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  errorp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * make_buffer () ; 
 int /*<<< orphan*/ * make_strtok (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned char peek () ; 
 int /*<<< orphan*/  pos ; 
 int read_escaped_char () ; 
 int readc () ; 
 int /*<<< orphan*/  write_utf8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Token *read_string(int enc) {
    Buffer *b = make_buffer();
    for (;;) {
        int c = readc();
        if (c == EOF)
            errorp(pos, "unterminated string");
        if (c == '"')
            break;
        if (c != '\\') {
            buf_write(b, c);
            continue;
        }
        bool isucs = (peek() == 'u' || peek() == 'U');
        c = read_escaped_char();
        if (isucs) {
            write_utf8(b, c);
            continue;
        }
        buf_write(b, c);
    }
    buf_write(b, '\0');
    return make_strtok(buf_body(b), buf_len(b), enc);
}