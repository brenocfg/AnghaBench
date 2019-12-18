#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;

/* Variables and functions */
 int /*<<< orphan*/  define_builtin (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_ptr_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/ * make_vector1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_int ; 
 int /*<<< orphan*/  type_void ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void parse_init() {
    Vector *voidptr = make_vector1(make_ptr_type(type_void));
    Vector *two_voidptrs = make_vector();
    vec_push(two_voidptrs, make_ptr_type(type_void));
    vec_push(two_voidptrs, make_ptr_type(type_void));
    define_builtin("__builtin_return_address", make_ptr_type(type_void), voidptr);
    define_builtin("__builtin_reg_class", type_int, voidptr);
    define_builtin("__builtin_va_arg", type_void, two_voidptrs);
    define_builtin("__builtin_va_start", type_void, voidptr);
}