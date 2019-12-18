#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_4__ {int len; int size; TYPE_2__* ptr; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_5__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/ * get () ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ *,char) ; 
 int maybe_read_brace () ; 
 int /*<<< orphan*/  maybe_skip_comma () ; 
 int /*<<< orphan*/ * peek () ; 
 int /*<<< orphan*/  read_initializer_elem (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 int read_intexpr () ; 
 int /*<<< orphan*/  skip_to_brace () ; 
 int /*<<< orphan*/  unget_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_array_initializer_sub(Vector *inits, Type *ty, int off, bool designated) {
    bool has_brace = maybe_read_brace();
    bool flexible = (ty->len <= 0);
    int elemsize = ty->ptr->size;
    int i;
    for (i = 0; flexible || i < ty->len; i++) {
        Token *tok = get();
        if (is_keyword(tok, '}')) {
            if (!has_brace)
                unget_token(tok);
            goto finish;
        }
        if ((is_keyword(tok, '.') || is_keyword(tok, '[')) && !has_brace && !designated) {
            unget_token(tok);
            return;
        }
        if (is_keyword(tok, '[')) {
            Token *tok = peek();
            int idx = read_intexpr();
            if (idx < 0 || (!flexible && ty->len <= idx))
                errort(tok, "array designator exceeds array bounds: %d", idx);
            i = idx;
            expect(']');
            designated = true;
        } else {
            unget_token(tok);
        }
        read_initializer_elem(inits, ty->ptr, off + elemsize * i, designated);
        maybe_skip_comma();
        designated = false;
    }
    if (has_brace)
        skip_to_brace();
 finish:
    if (ty->len < 0) {
        ty->len = i;
        ty->size = elemsize * i;
    }
}