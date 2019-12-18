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
struct TYPE_6__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 scalar_t__ KIND_ARRAY ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit (char*,char*,char*) ; 
 char* format (char*,char*,int) ; 
 char* get_int_reg (TYPE_1__*,char) ; 
 int /*<<< orphan*/  maybe_convert_bool (TYPE_1__*) ; 
 int /*<<< orphan*/  maybe_emit_bitshift_save (TYPE_1__*,char*) ; 

__attribute__((used)) static void emit_gsave(char *varname, Type *ty, int off) {
    SAVE;
    assert(ty->kind != KIND_ARRAY);
    maybe_convert_bool(ty);
    char *reg = get_int_reg(ty, 'a');
    char *addr = format("%s+%d(%%rip)", varname, off);
    maybe_emit_bitshift_save(ty, addr);
    emit("mov #%s, %s", reg, addr);
}