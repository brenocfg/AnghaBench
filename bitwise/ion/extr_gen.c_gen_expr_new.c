#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* base; } ;
typedef  TYPE_2__ Type ;
struct TYPE_9__ {scalar_t__ arg; scalar_t__ len; scalar_t__ alloc; } ;
struct TYPE_11__ {scalar_t__ kind; TYPE_1__ new_expr; } ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 scalar_t__ EXPR_NEW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gen_expr (scalar_t__) ; 
 int /*<<< orphan*/  genf (char*,...) ; 
 TYPE_2__* get_resolved_type (TYPE_3__*) ; 
 int is_ptr_type (TYPE_2__*) ; 
 char* type_to_cdecl (TYPE_2__*,char*) ; 

void gen_expr_new(Expr *expr) {
    assert(expr->kind == EXPR_NEW);
    Type *type = get_resolved_type(expr);
    assert(is_ptr_type(type));
    const char *type_cdecl = type_to_cdecl(type, "");
    const char *base_cdecl = type_to_cdecl(type->base, "");
    if (expr->new_expr.alloc) {
        if (expr->new_expr.len) {
            if (!expr->new_expr.arg) {
                genf("((%s)generic_alloc((Allocator *)(", type_cdecl);
                gen_expr(expr->new_expr.alloc);
                genf("), ");
                gen_expr(expr->new_expr.len);
                genf("* sizeof(%s), alignof(%s)))", base_cdecl, base_cdecl);
            } else {
                genf("((%s)generic_alloc_copy((Allocator *)(", type_cdecl);
                gen_expr(expr->new_expr.alloc);
                genf("), ");
                gen_expr(expr->new_expr.len);
                genf(" * sizeof(%s), alignof(%s), &(", base_cdecl, base_cdecl);
                gen_expr(expr->new_expr.arg);
                genf(")))");
            }
        } else {
            if (!expr->new_expr.arg) {
                genf("((%s)generic_alloc((Allocator *)(", type_cdecl);
                gen_expr(expr->new_expr.alloc);
                genf("), ");
                genf("sizeof(%s), alignof(%s)))", base_cdecl, base_cdecl);
            } else {
                genf("((%s)generic_alloc_copy((Allocator *)(", type_cdecl);
                gen_expr(expr->new_expr.alloc);
                genf("), ");
                genf("sizeof(%s), alignof(%s), &(", base_cdecl, base_cdecl, base_cdecl);
                gen_expr(expr->new_expr.arg);
                genf(")))");
            }
        }
    } else {
        if (expr->new_expr.len) {
            if (!expr->new_expr.arg) {
                genf("((%s)tls_alloc(", type_cdecl);
                gen_expr(expr->new_expr.len);
                genf(" * sizeof(%s), alignof(%s)))", base_cdecl, base_cdecl);
            } else {
                genf("((%s)alloc_copy(", type_cdecl);
                gen_expr(expr->new_expr.len);
                genf(" * sizeof(%s), alignof(%s), &(", base_cdecl, base_cdecl);
                gen_expr(expr->new_expr.arg);
                genf(")))");
            }
        } else {
            if (!expr->new_expr.arg) {
                genf("((%s)tls_alloc(sizeof(%s), alignof(%s)))", type_cdecl, base_cdecl, base_cdecl);
            } else {
                genf("((%s)alloc_copy(sizeof(%s), alignof(%s), &(", type_cdecl, base_cdecl, base_cdecl);
                gen_expr(expr->new_expr.arg);
                genf(")))");
            }
        }
    }
}