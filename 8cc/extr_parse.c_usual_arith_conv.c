#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ kind; scalar_t__ size; scalar_t__ usig; } ;
typedef  TYPE_1__ Type ;
struct TYPE_12__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* copy_type (TYPE_1__*) ; 
 int is_arithtype (TYPE_1__*) ; 
 scalar_t__ is_flotype (TYPE_1__*) ; 
 scalar_t__ is_inttype (TYPE_1__*) ; 
 TYPE_5__* type_int ; 

__attribute__((used)) static Type *usual_arith_conv(Type *t, Type *u) {
    assert(is_arithtype(t));
    assert(is_arithtype(u));
    if (t->kind < u->kind) {
        // Make t the larger type
        Type *tmp = t;
        t = u;
        u = tmp;
    }
    if (is_flotype(t))
        return t;
    assert(is_inttype(t) && t->size >= type_int->size);
    assert(is_inttype(u) && u->size >= type_int->size);
    if (t->size > u->size)
        return t;
    assert(t->size == u->size);
    if (t->usig == u->usig)
        return t;
    Type *r = copy_type(t);
    r->usig = true;
    return r;
}