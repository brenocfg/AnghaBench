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
struct TYPE_7__ {scalar_t__ kind; int bol; int column; } ;
typedef  TYPE_1__ Token ;
struct TYPE_8__ {int column; } ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ TIDENT ; 
 TYPE_6__* current_file () ; 
 scalar_t__ is_ident (TYPE_1__*,char*) ; 
 TYPE_1__* lex () ; 
 TYPE_1__* make_keyword (char) ; 
 int readc () ; 
 int /*<<< orphan*/  skip_char () ; 
 int /*<<< orphan*/  skip_line () ; 
 int /*<<< orphan*/  skip_space () ; 
 int /*<<< orphan*/  skip_string () ; 
 int /*<<< orphan*/  unget_token (TYPE_1__*) ; 

void skip_cond_incl() {
    int nest = 0;
    for (;;) {
        bool bol = (current_file()->column == 1);
        skip_space();
        int c = readc();
        if (c == EOF)
            return;
        if (c == '\'') {
            skip_char();
            continue;
        }
        if (c == '\"') {
            skip_string();
            continue;
        }
        if (c != '#' || !bol)
            continue;
        int column = current_file()->column - 1;
        Token *tok = lex();
        if (tok->kind != TIDENT)
            continue;
        if (!nest && (is_ident(tok, "else") || is_ident(tok, "elif") || is_ident(tok, "endif"))) {
            unget_token(tok);
            Token *hash = make_keyword('#');
            hash->bol = true;
            hash->column = column;
            unget_token(hash);
            return;
        }
        if (is_ident(tok, "if") || is_ident(tok, "ifdef") || is_ident(tok, "ifndef"))
            nest++;
        else if (nest && is_ident(tok, "endif"))
            nest--;
        skip_line();
    }
}