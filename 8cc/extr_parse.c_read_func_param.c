#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ kind; struct TYPE_9__* ptr; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_PARAM ; 
 int /*<<< orphan*/  DECL_PARAM_TYPEONLY ; 
 scalar_t__ KIND_ARRAY ; 
 scalar_t__ KIND_FUNC ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_type (int /*<<< orphan*/ ) ; 
 TYPE_1__* make_ptr_type (TYPE_1__*) ; 
 int /*<<< orphan*/  peek () ; 
 TYPE_1__* read_decl_spec (int*) ; 
 TYPE_1__* read_declarator (char**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2s (int /*<<< orphan*/ ) ; 
 TYPE_1__* type_int ; 

__attribute__((used)) static Type *read_func_param(char **name, bool optional) {
    int sclass = 0;
    Type *basety = type_int;
    if (is_type(peek())) {
        basety = read_decl_spec(&sclass);
    } else if (optional) {
        errort(peek(), "type expected, but got %s", tok2s(peek()));
    }
    Type *ty = read_declarator(name, basety, NULL, optional ? DECL_PARAM_TYPEONLY : DECL_PARAM);
    // C11 6.7.6.3p7: Array of T is adjusted to pointer to T
    // in a function parameter list.
    if (ty->kind == KIND_ARRAY)
        return make_ptr_type(ty->ptr);
    // C11 6.7.6.3p8: Function is adjusted to pointer to function
    // in a function parameter list.
    if (ty->kind == KIND_FUNC)
        return make_ptr_type(ty);
    return ty;
}