#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_9__ {scalar_t__ bitsize; } ;
struct TYPE_8__ {scalar_t__ kind; } ;
struct TYPE_7__ {scalar_t__ kind; scalar_t__ initoff; TYPE_4__* totype; TYPE_3__* initval; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 scalar_t__ AST_INIT ; 
 scalar_t__ AST_LITERAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_expr (TYPE_3__*) ; 
 int /*<<< orphan*/  emit_fill_holes (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  emit_lsave (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  emit_save_literal (TYPE_3__*,TYPE_4__*,scalar_t__) ; 
 TYPE_1__* vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emit_decl_init(Vector *inits, int off, int totalsize) {
    emit_fill_holes(inits, off, totalsize);
    for (int i = 0; i < vec_len(inits); i++) {
        Node *node = vec_get(inits, i);
        assert(node->kind == AST_INIT);
        bool isbitfield = (node->totype->bitsize > 0);
        if (node->initval->kind == AST_LITERAL && !isbitfield) {
            emit_save_literal(node->initval, node->totype, node->initoff + off);
        } else {
            emit_expr(node->initval);
            emit_lsave(node->totype, node->initoff + off);
        }
    }
}