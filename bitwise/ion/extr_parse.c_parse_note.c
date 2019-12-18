#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  NoteArg ;
typedef  int /*<<< orphan*/  Note ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COMMA ; 
 int /*<<< orphan*/  TOKEN_LPAREN ; 
 int /*<<< orphan*/  TOKEN_RPAREN ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_note (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* parse_name () ; 
 int /*<<< orphan*/  parse_note_arg () ; 
 TYPE_1__ token ; 

Note parse_note(void) {
    SrcPos pos = token.pos;
    const char *name = parse_name();
    NoteArg *args = NULL;
    if (match_token(TOKEN_LPAREN)) {
        buf_push(args, parse_note_arg());
        while (match_token(TOKEN_COMMA)) {
            buf_push(args, parse_note_arg());
        }
        expect_token(TOKEN_RPAREN);
    }
    return new_note(pos, name, args, buf_len(args));
}