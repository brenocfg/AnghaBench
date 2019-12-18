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

/* Variables and functions */
 int ENC_NONE ; 
 int /*<<< orphan*/  errorp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * make_char (int,int) ; 
 int /*<<< orphan*/  pos ; 
 int read_escaped_char () ; 
 int readc () ; 

__attribute__((used)) static Token *read_char(int enc) {
    int c = readc();
    int r = (c == '\\') ? read_escaped_char() : c;
    c = readc();
    if (c != '\'')
        errorp(pos, "unterminated char");
    if (enc == ENC_NONE)
        return make_char((char)r, enc);
    return make_char(r, enc);
}