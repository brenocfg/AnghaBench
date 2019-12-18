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
 int /*<<< orphan*/  buf_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,char) ; 
 scalar_t__ isalnum (char) ; 
 int /*<<< orphan*/ * make_buffer () ; 
 int /*<<< orphan*/ * make_ident (int /*<<< orphan*/ ) ; 
 unsigned char peek () ; 
 int /*<<< orphan*/  read_escaped_char () ; 
 char readc () ; 
 int /*<<< orphan*/  unreadc (char) ; 
 int /*<<< orphan*/  write_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Token *read_ident(char c) {
    Buffer *b = make_buffer();
    buf_write(b, c);
    for (;;) {
        c = readc();
        if (isalnum(c) || (c & 0x80) || c == '_' || c == '$') {
            buf_write(b, c);
            continue;
        }
        // C11 6.4.2.1: \u or \U characters (universal-character-name)
        // are allowed to be part of identifiers.
        if (c == '\\' && (peek() == 'u' || peek() == 'U')) {
            write_utf8(b, read_escaped_char());
            continue;
        }
        unreadc(c);
        buf_write(b, '\0');
        return make_ident(buf_body(b));
    }
}