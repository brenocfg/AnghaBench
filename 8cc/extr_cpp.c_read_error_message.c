#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kind; scalar_t__ space; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ TNEWLINE ; 
 char* buf_body (int /*<<< orphan*/ *) ; 
 scalar_t__ buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,char) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/ * make_buffer () ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 

__attribute__((used)) static char *read_error_message() {
    Buffer *b = make_buffer();
    for (;;) {
        Token *tok = lex();
        if (tok->kind == TNEWLINE)
            return buf_body(b);
        if (buf_len(b) != 0 && tok->space)
            buf_write(b, ' ');
        buf_printf(b, "%s", tok2s(tok));
    }
}