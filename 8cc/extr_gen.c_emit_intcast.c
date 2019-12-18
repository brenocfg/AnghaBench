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
struct TYPE_3__ {int kind; int /*<<< orphan*/  usig; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
#define  KIND_BOOL 133 
#define  KIND_CHAR 132 
#define  KIND_INT 131 
#define  KIND_LLONG 130 
#define  KIND_LONG 129 
#define  KIND_SHORT 128 
 int /*<<< orphan*/  emit (char*) ; 

__attribute__((used)) static void emit_intcast(Type *ty) {
    switch(ty->kind) {
    case KIND_BOOL:
    case KIND_CHAR:
        ty->usig ? emit("movzbq #al, #rax") : emit("movsbq #al, #rax");
        return;
    case KIND_SHORT:
        ty->usig ? emit("movzwq #ax, #rax") : emit("movswq #ax, #rax");
        return;
    case KIND_INT:
        ty->usig ? emit("mov #eax, #eax") : emit("cltq");
        return;
    case KIND_LONG:
    case KIND_LLONG:
        return;
    }
}