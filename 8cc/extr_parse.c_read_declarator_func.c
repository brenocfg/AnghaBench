#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_6__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 scalar_t__ KIND_ARRAY ; 
 scalar_t__ KIND_FUNC ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_1__* read_func_param_list (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Type *read_declarator_func(Type *basety, Vector *param) {
    if (basety->kind == KIND_FUNC)
        error("function returning a function");
    if (basety->kind == KIND_ARRAY)
        error("function returning an array");
    return read_func_param_list(param, basety);
}