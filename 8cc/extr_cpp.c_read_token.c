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
struct TYPE_8__ {scalar_t__ kind; int /*<<< orphan*/ * hideset; scalar_t__ bol; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ MIN_CPP_TOKEN ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 TYPE_1__* maybe_convert_keyword (TYPE_1__*) ; 
 int /*<<< orphan*/  read_directive (TYPE_1__*) ; 
 TYPE_1__* read_expand () ; 

Token *read_token() {
    Token *tok;
    for (;;) {
        tok = read_expand();
        if (tok->bol && is_keyword(tok, '#') && tok->hideset == NULL) {
            read_directive(tok);
            continue;
        }
        assert(tok->kind < MIN_CPP_TOKEN);
        return maybe_convert_keyword(tok);
    }
}