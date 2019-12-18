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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_package ; 
 int /*<<< orphan*/  sym_global_type (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_bool ; 
 int /*<<< orphan*/  type_char ; 
 int /*<<< orphan*/  type_double ; 
 int /*<<< orphan*/  type_float ; 
 int /*<<< orphan*/  type_int ; 
 int /*<<< orphan*/  type_llong ; 
 int /*<<< orphan*/  type_long ; 
 int /*<<< orphan*/  type_schar ; 
 int /*<<< orphan*/  type_short ; 
 int /*<<< orphan*/  type_uchar ; 
 int /*<<< orphan*/  type_uint ; 
 int /*<<< orphan*/  type_ullong ; 
 int /*<<< orphan*/  type_ulong ; 
 int /*<<< orphan*/  type_ushort ; 
 int /*<<< orphan*/  type_void ; 

void init_builtin_syms() {
    assert(current_package);
    sym_global_type("void", type_void);
    sym_global_type("bool", type_bool);
    sym_global_type("char", type_char);
    sym_global_type("schar", type_schar);
    sym_global_type("uchar", type_uchar);
    sym_global_type("short", type_short);
    sym_global_type("ushort", type_ushort);
    sym_global_type("int", type_int);
    sym_global_type("uint", type_uint);
    sym_global_type("long", type_long);
    sym_global_type("ulong", type_ulong);
    sym_global_type("llong", type_llong);
    sym_global_type("ullong", type_ullong);
    sym_global_type("float", type_float);
    sym_global_type("double", type_double);
}