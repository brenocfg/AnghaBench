#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int kind; char* sval; int /*<<< orphan*/  enc; scalar_t__ slen; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_NONE ; 
 TYPE_1__* copy_token (TYPE_1__*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  unget_token (TYPE_1__*) ; 

__attribute__((used)) static void make_token_pushback(Token *tmpl, int kind, char *sval) {
    Token *tok = copy_token(tmpl);
    tok->kind = kind;
    tok->sval = sval;
    tok->slen = strlen(sval) + 1;
    tok->enc = ENC_NONE;
    unget_token(tok);
}