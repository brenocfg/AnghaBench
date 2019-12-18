#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_9__ {scalar_t__ kind; int /*<<< orphan*/  init; int /*<<< orphan*/  index; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {size_t num_fields; TYPE_3__* fields; scalar_t__ type; } ;
struct TYPE_8__ {TYPE_1__ compound; } ;
typedef  TYPE_2__ Expr ;
typedef  TYPE_3__ CompoundField ;

/* Variables and functions */
 scalar_t__ FIELD_INDEX ; 
 scalar_t__ FIELD_NAME ; 
 int /*<<< orphan*/  gen_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genf (char*,...) ; 
 int /*<<< orphan*/ * get_resolved_expected_type (TYPE_2__*) ; 
 int /*<<< orphan*/  get_resolved_type (TYPE_2__*) ; 
 int /*<<< orphan*/  is_ptr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_to_cdecl (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  typespec_to_cdecl (scalar_t__,char*) ; 

void gen_expr_compound(Expr *expr) {
    Type *expected_type = get_resolved_expected_type(expr);
    if (expected_type && !is_ptr_type(expected_type)) {
        genf("{");
    } else if (expr->compound.type) {
        genf("(%s){", typespec_to_cdecl(expr->compound.type, ""));
    } else {
        genf("(%s){", type_to_cdecl(get_resolved_type(expr), ""));
    }
    for (size_t i = 0; i < expr->compound.num_fields; i++) {
        if (i != 0) {
            genf(", ");
        }
        CompoundField field = expr->compound.fields[i];
        if (field.kind == FIELD_NAME) {
            genf(".%s = ", field.name);
        } else if (field.kind == FIELD_INDEX) {
            genf("[");
            gen_expr(field.index);
            genf("] = ");
        }
        gen_expr(field.init);
    }
    if (expr->compound.num_fields == 0) {
        genf("0");
    }
    genf("}");
}