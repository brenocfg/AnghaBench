#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int kind; int usig; int size; int align; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 int KIND_BOOL ; 
 int KIND_CHAR ; 
 int KIND_DOUBLE ; 
 int KIND_FLOAT ; 
 int KIND_INT ; 
 int KIND_LDOUBLE ; 
 int KIND_LLONG ; 
 int KIND_LONG ; 
 int KIND_SHORT ; 
 int KIND_VOID ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static Type *make_numtype(int kind, bool usig) {
    Type *r = calloc(1, sizeof(Type));
    r->kind = kind;
    r->usig = usig;
    if (kind == KIND_VOID)         r->size = r->align = 0;
    else if (kind == KIND_BOOL)    r->size = r->align = 1;
    else if (kind == KIND_CHAR)    r->size = r->align = 1;
    else if (kind == KIND_SHORT)   r->size = r->align = 2;
    else if (kind == KIND_INT)     r->size = r->align = 4;
    else if (kind == KIND_LONG)    r->size = r->align = 8;
    else if (kind == KIND_LLONG)   r->size = r->align = 8;
    else if (kind == KIND_FLOAT)   r->size = r->align = 4;
    else if (kind == KIND_DOUBLE)  r->size = r->align = 8;
    else if (kind == KIND_LDOUBLE) r->size = r->align = 8;
    else error("internal error");
    return r;
}