#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int loff; TYPE_1__* ty; int /*<<< orphan*/  localvars; int /*<<< orphan*/  params; int /*<<< orphan*/  fname; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; scalar_t__ hasva; int /*<<< orphan*/  isstatic; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  SAVE ; 
 int align (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  emit_noindent (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ emit_regsave_area () ; 
 int /*<<< orphan*/  push (char*) ; 
 int /*<<< orphan*/  push_func_params (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_reg_nums (int /*<<< orphan*/ ) ; 
 int stackpos ; 
 TYPE_2__* vec_get (int /*<<< orphan*/ ,int) ; 
 int vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_func_prologue(Node *func) {
    SAVE;
    emit(".text");
    if (!func->ty->isstatic)
        emit_noindent(".global %s", func->fname);
    emit_noindent("%s:", func->fname);
    emit("nop");
    push("rbp");
    emit("mov #rsp, #rbp");
    int off = 0;
    if (func->ty->hasva) {
        set_reg_nums(func->params);
        off -= emit_regsave_area();
    }
    push_func_params(func->params, off);
    off -= vec_len(func->params) * 8;

    int localarea = 0;
    for (int i = 0; i < vec_len(func->localvars); i++) {
        Node *v = vec_get(func->localvars, i);
        int size = align(v->ty->size, 8);
        assert(size % 8 == 0);
        off -= size;
        v->loff = off;
        localarea += size;
    }
    if (localarea) {
        emit("sub $%d, #rsp", localarea);
        stackpos += localarea;
    }
}