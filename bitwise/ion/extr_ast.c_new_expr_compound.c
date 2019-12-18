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
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_5__ {size_t num_fields; int /*<<< orphan*/  fields; int /*<<< orphan*/ * type; } ;
struct TYPE_6__ {TYPE_1__ compound; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;
typedef  int /*<<< orphan*/  CompoundField ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DUP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXPR_COMPOUND ; 
 TYPE_2__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_compound(SrcPos pos, Typespec *type, CompoundField *fields, size_t num_fields) {
    Expr *e = new_expr(EXPR_COMPOUND, pos);
    e->compound.type = type;
    e->compound.fields = AST_DUP(fields);
    e->compound.num_fields = num_fields;
    return e;
}