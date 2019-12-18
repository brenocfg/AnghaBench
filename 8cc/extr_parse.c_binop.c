#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;
struct TYPE_20__ {TYPE_1__* ty; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 scalar_t__ KIND_PTR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* ast_binop (TYPE_1__*,int,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  is_arithtype (TYPE_1__*) ; 
 TYPE_1__* type_int ; 
 TYPE_1__* type_long ; 
 TYPE_1__* usual_arith_conv (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  valid_pointer_binop (int) ; 
 TYPE_2__* wrap (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static Node *binop(int op, Node *lhs, Node *rhs) {
    if (lhs->ty->kind == KIND_PTR && rhs->ty->kind == KIND_PTR) {
        if (!valid_pointer_binop(op))
            error("invalid pointer arith");
        // C11 6.5.6.9: Pointer subtractions have type ptrdiff_t.
        if (op == '-')
            return ast_binop(type_long, op, lhs, rhs);
        // C11 6.5.8.6, 6.5.9.3: Pointer comparisons have type int.
        return ast_binop(type_int, op, lhs, rhs);
    }
    if (lhs->ty->kind == KIND_PTR)
        return ast_binop(lhs->ty, op, lhs, rhs);
    if (rhs->ty->kind == KIND_PTR)
        return ast_binop(rhs->ty, op, rhs, lhs);
    assert(is_arithtype(lhs->ty));
    assert(is_arithtype(rhs->ty));
    Type *r = usual_arith_conv(lhs->ty, rhs->ty);
    return ast_binop(r, op, wrap(r, lhs), wrap(r, rhs));
}