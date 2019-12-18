#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Token ;
struct TYPE_11__ {scalar_t__ kind; } ;
struct TYPE_10__ {TYPE_1__* ty; } ;
struct TYPE_9__ {scalar_t__ kind; TYPE_7__* ptr; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DEREF ; 
 scalar_t__ KIND_FUNC ; 
 scalar_t__ KIND_PTR ; 
 TYPE_2__* ast_uop (int /*<<< orphan*/ ,TYPE_7__*,TYPE_2__*) ; 
 TYPE_2__* conv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node2s (TYPE_2__*) ; 
 int /*<<< orphan*/  read_cast_expr () ; 

__attribute__((used)) static Node *read_unary_deref(Token *tok) {
    Node *operand = conv(read_cast_expr());
    if (operand->ty->kind != KIND_PTR)
        errort(tok, "pointer type expected, but got %s", node2s(operand));
    if (operand->ty->ptr->kind == KIND_FUNC)
        return operand;
    return ast_uop(AST_DEREF, operand->ty->ptr, operand);
}