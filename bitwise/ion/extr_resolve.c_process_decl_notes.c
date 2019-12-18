#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  pos; } ;
struct TYPE_12__ {char* val; } ;
struct TYPE_15__ {scalar_t__ kind; TYPE_2__ str_lit; } ;
struct TYPE_14__ {int num_args; TYPE_1__* args; } ;
struct TYPE_13__ {char* name; char const* external_name; } ;
struct TYPE_11__ {TYPE_5__* expr; } ;
typedef  TYPE_3__ Sym ;
typedef  TYPE_4__ Note ;
typedef  TYPE_5__ Expr ;
typedef  TYPE_6__ Decl ;

/* Variables and functions */
 scalar_t__ EXPR_STR ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  foreign_name ; 
 TYPE_4__* get_decl_note (TYPE_6__*,int /*<<< orphan*/ ) ; 

void process_decl_notes(Decl *decl, Sym *sym) {
    Note *foreign_note = get_decl_note(decl, foreign_name);
    if (foreign_note) {
        if (foreign_note->num_args > 1) {
            fatal_error(decl->pos, "@foreign takes 0 or 1 argument");
        }
        const char *external_name;
        if (foreign_note->num_args == 0) {
            external_name = sym->name;
        } else {
            Expr *arg = foreign_note->args[0].expr;
            if (arg->kind != EXPR_STR) {
                fatal_error(decl->pos, "@foreign argument 1 must be a string literal");
            }
            external_name = arg->str_lit.val;
        }
        sym->external_name = external_name;
    }
}