#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 scalar_t__ KIND_BOOL ; 
 scalar_t__ KIND_DOUBLE ; 
 scalar_t__ KIND_FLOAT ; 
 scalar_t__ KIND_LDOUBLE ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit (char*) ; 
 int /*<<< orphan*/  emit_intcast (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_to_bool (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_toint (TYPE_1__*) ; 
 scalar_t__ is_inttype (TYPE_1__*) ; 

__attribute__((used)) static void emit_load_convert(Type *to, Type *from) {
    SAVE;
    if (is_inttype(from) && to->kind == KIND_FLOAT)
        emit("cvtsi2ss #eax, #xmm0");
    else if (is_inttype(from) && to->kind == KIND_DOUBLE)
        emit("cvtsi2sd #eax, #xmm0");
    else if (from->kind == KIND_FLOAT && to->kind == KIND_DOUBLE)
        emit("cvtps2pd #xmm0, #xmm0");
    else if ((from->kind == KIND_DOUBLE || from->kind == KIND_LDOUBLE) && to->kind == KIND_FLOAT)
        emit("cvtpd2ps #xmm0, #xmm0");
    else if (to->kind == KIND_BOOL)
        emit_to_bool(from);
    else if (is_inttype(from) && is_inttype(to))
        emit_intcast(from);
    else if (is_inttype(to))
        emit_toint(from);
}