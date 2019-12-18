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
struct TYPE_3__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 scalar_t__ KIND_DOUBLE ; 
 scalar_t__ KIND_FLOAT ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit (char*) ; 

__attribute__((used)) static void emit_toint(Type *ty) {
    SAVE;
    if (ty->kind == KIND_FLOAT)
        emit("cvttss2si #xmm0, #eax");
    else if (ty->kind == KIND_DOUBLE)
        emit("cvttsd2si #xmm0, #eax");
}