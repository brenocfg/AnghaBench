#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_7__ {scalar_t__ kind; int space; int bol; } ;
typedef  TYPE_1__ Token ;
struct TYPE_8__ {int column; } ;

/* Variables and functions */
 scalar_t__ TSPACE ; 
 int /*<<< orphan*/ * buffers ; 
 TYPE_6__* current_file () ; 
 TYPE_1__* do_read_token () ; 
 TYPE_1__* eof_token ; 
 int vec_len (int /*<<< orphan*/ *) ; 
 TYPE_1__* vec_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vec_tail (int /*<<< orphan*/ *) ; 

Token *lex() {
    Vector *buf = vec_tail(buffers);
    if (vec_len(buf) > 0)
        return vec_pop(buf);
    if (vec_len(buffers) > 1)
        return eof_token;
    bool bol = (current_file()->column == 1);
    Token *tok = do_read_token();
    while (tok->kind == TSPACE) {
        tok = do_read_token();
        tok->space = true;
    }
    tok->bol = bol;
    return tok;
}