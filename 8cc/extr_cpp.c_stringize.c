#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_8__ {int /*<<< orphan*/  enc; scalar_t__ slen; int /*<<< orphan*/  sval; int /*<<< orphan*/  kind; scalar_t__ space; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_NONE ; 
 int /*<<< orphan*/  TSTRING ; 
 int /*<<< orphan*/  buf_body (int /*<<< orphan*/ *) ; 
 scalar_t__ buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,char) ; 
 TYPE_1__* copy_token (TYPE_1__*) ; 
 int /*<<< orphan*/ * make_buffer () ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 
 TYPE_1__* vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Token *stringize(Token *tmpl, Vector *args) {
    Buffer *b = make_buffer();
    for (int i = 0; i < vec_len(args); i++) {
        Token *tok = vec_get(args, i);
        if (buf_len(b) && tok->space)
            buf_printf(b, " ");
        buf_printf(b, "%s", tok2s(tok));
    }
    buf_write(b, '\0');
    Token *r = copy_token(tmpl);
    r->kind = TSTRING;
    r->sval = buf_body(b);
    r->slen = buf_len(b);
    r->enc = ENC_NONE;
    return r;
}