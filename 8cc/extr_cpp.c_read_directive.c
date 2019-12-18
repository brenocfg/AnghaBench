#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ kind; char* sval; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TIDENT ; 
 scalar_t__ TNEWLINE ; 
 scalar_t__ TNUMBER ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/  read_define () ; 
 int /*<<< orphan*/  read_elif (TYPE_1__*) ; 
 int /*<<< orphan*/  read_else (TYPE_1__*) ; 
 int /*<<< orphan*/  read_endif (TYPE_1__*) ; 
 int /*<<< orphan*/  read_error (TYPE_1__*) ; 
 int /*<<< orphan*/  read_if () ; 
 int /*<<< orphan*/  read_ifdef () ; 
 int /*<<< orphan*/  read_ifndef () ; 
 int /*<<< orphan*/  read_include (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_include_next (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_line () ; 
 int /*<<< orphan*/  read_linemarker (TYPE_1__*) ; 
 int /*<<< orphan*/  read_pragma () ; 
 int /*<<< orphan*/  read_undef () ; 
 int /*<<< orphan*/  read_warning (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 

__attribute__((used)) static void read_directive(Token *hash) {
    Token *tok = lex();
    if (tok->kind == TNEWLINE)
        return;
    if (tok->kind == TNUMBER) {
        read_linemarker(tok);
        return;
    }
    if (tok->kind != TIDENT)
        goto err;
    char *s = tok->sval;
    if (!strcmp(s, "define"))            read_define();
    else if (!strcmp(s, "elif"))         read_elif(hash);
    else if (!strcmp(s, "else"))         read_else(hash);
    else if (!strcmp(s, "endif"))        read_endif(hash);
    else if (!strcmp(s, "error"))        read_error(hash);
    else if (!strcmp(s, "if"))           read_if();
    else if (!strcmp(s, "ifdef"))        read_ifdef();
    else if (!strcmp(s, "ifndef"))       read_ifndef();
    else if (!strcmp(s, "import"))       read_include(hash, tok->file, true);
    else if (!strcmp(s, "include"))      read_include(hash, tok->file, false);
    else if (!strcmp(s, "include_next")) read_include_next(hash, tok->file);
    else if (!strcmp(s, "line"))         read_line();
    else if (!strcmp(s, "pragma"))       read_pragma();
    else if (!strcmp(s, "undef"))        read_undef();
    else if (!strcmp(s, "warning"))      read_warning(hash);
    else goto err;
    return;

  err:
    errort(hash, "unsupported preprocessor directive: %s", tok2s(tok));
}