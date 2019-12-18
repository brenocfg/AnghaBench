#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_11__ {int /*<<< orphan*/  is_struct; scalar_t__ offset; int /*<<< orphan*/  fields; } ;
typedef  TYPE_1__ Type ;
struct TYPE_12__ {scalar_t__ kind; char* sval; } ;
typedef  TYPE_2__ Token ;

/* Variables and functions */
 scalar_t__ TIDENT ; 
 TYPE_1__* dict_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dict_keys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errort (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get () ; 
 scalar_t__ is_keyword (TYPE_2__*,char) ; 
 int maybe_read_brace () ; 
 int /*<<< orphan*/  maybe_skip_comma () ; 
 int /*<<< orphan*/  read_initializer_elem (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  skip_to_brace () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  tok2s (TYPE_2__*) ; 
 int /*<<< orphan*/  unget_token (TYPE_2__*) ; 
 char* vec_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_struct_initializer_sub(Vector *inits, Type *ty, int off, bool designated) {
    bool has_brace = maybe_read_brace();
    Vector *keys = dict_keys(ty->fields);
    int i = 0;
    for (;;) {
        Token *tok = get();
        if (is_keyword(tok, '}')) {
            if (!has_brace)
                unget_token(tok);
            return;
        }
        char *fieldname;
        Type *fieldtype;
        if ((is_keyword(tok, '.') || is_keyword(tok, '[')) && !has_brace && !designated) {
            unget_token(tok);
            return;
        }
        if (is_keyword(tok, '.')) {
            tok = get();
            if (!tok || tok->kind != TIDENT)
                errort(tok, "malformed desginated initializer: %s", tok2s(tok));
            fieldname = tok->sval;
            fieldtype = dict_get(ty->fields, fieldname);
            if (!fieldtype)
                errort(tok, "field does not exist: %s", tok2s(tok));
            keys = dict_keys(ty->fields);
            i = 0;
            while (i < vec_len(keys)) {
                char *s = vec_get(keys, i++);
                if (strcmp(fieldname, s) == 0)
                    break;
            }
            designated = true;
        } else {
            unget_token(tok);
            if (i == vec_len(keys))
                break;
            fieldname = vec_get(keys, i++);
            fieldtype = dict_get(ty->fields, fieldname);
        }
        read_initializer_elem(inits, fieldtype, off + fieldtype->offset, designated);
        maybe_skip_comma();
        designated = false;
        if (!ty->is_struct)
            break;
    }
    if (has_brace)
        skip_to_brace();
}