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
typedef  int /*<<< orphan*/  TypespecKind ;
struct TYPE_4__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ Typespec ;
typedef  int /*<<< orphan*/  SrcPos ;

/* Variables and functions */
 TYPE_1__* ast_alloc (int) ; 

Typespec *new_typespec(TypespecKind kind, SrcPos pos) {
    Typespec *t = ast_alloc(sizeof(Typespec));
    t->kind = kind;
    t->pos = pos;
    return t;
}