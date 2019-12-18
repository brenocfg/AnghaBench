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
typedef  int /*<<< orphan*/  Pos ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/ * do_read_token () ; 
 int /*<<< orphan*/  errorp (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  get_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_file_string (char*) ; 
 int /*<<< orphan*/  next (char) ; 
 scalar_t__ peek () ; 
 int /*<<< orphan*/  stream_stash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_unstash () ; 

Token *lex_string(char *s) {
    stream_stash(make_file_string(s));
    Token *r = do_read_token();
    next('\n');
    Pos p = get_pos(0);
    if (peek() != EOF)
        errorp(p, "unconsumed input: %s", s);
    stream_unstash();
    return r;
}