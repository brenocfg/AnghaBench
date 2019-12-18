#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ kind; char* sval; } ;
typedef  TYPE_1__ Token ;
struct TYPE_8__ {int line; char* name; } ;
typedef  TYPE_2__ File ;

/* Variables and functions */
 scalar_t__ TNEWLINE ; 
 scalar_t__ TNUMBER ; 
 scalar_t__ TSTRING ; 
 int atoi (char*) ; 
 TYPE_2__* current_file () ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_newline () ; 
 int /*<<< orphan*/  is_digit_sequence (char*) ; 
 TYPE_1__* read_expand_newline () ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 

__attribute__((used)) static void read_line() {
    Token *tok = read_expand_newline();
    if (tok->kind != TNUMBER || !is_digit_sequence(tok->sval))
        errort(tok, "number expected after #line, but got %s", tok2s(tok));
    int line = atoi(tok->sval);
    tok = read_expand_newline();
    char *filename = NULL;
    if (tok->kind == TSTRING) {
        filename = tok->sval;
        expect_newline();
    } else if (tok->kind != TNEWLINE) {
        errort(tok, "newline or a source name are expected, but got %s", tok2s(tok));
    }
    File *f = current_file();
    f->line = line;
    if (filename)
        f->name = filename;
}