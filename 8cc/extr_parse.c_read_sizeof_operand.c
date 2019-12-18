#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ kind; int size; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ KIND_FUNC ; 
 scalar_t__ KIND_VOID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * ast_inttype (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* read_sizeof_operand_sub () ; 
 int /*<<< orphan*/  type_ulong ; 

__attribute__((used)) static Node *read_sizeof_operand() {
    Type *ty = read_sizeof_operand_sub();
    // Sizeof on void or function type is GNU extension
    int size = (ty->kind == KIND_VOID || ty->kind == KIND_FUNC) ? 1 : ty->size;
    assert(0 <= size);
    return ast_inttype(type_ulong, size);
}