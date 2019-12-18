#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  align; int /*<<< orphan*/  size; struct TYPE_6__* base; int /*<<< orphan*/ * sym; } ;
typedef  TYPE_1__ Type ;
struct TYPE_7__ {int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  Sym ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_ENUM ; 
 TYPE_1__* type_alloc (int /*<<< orphan*/ ) ; 
 TYPE_2__* type_int ; 

Type *type_enum(Sym *sym, Type *base) {
    Type *type = type_alloc(TYPE_ENUM);
    type->sym = sym;
    type->base = base;
    type->size = type_int->size;
    type->align = type_int->align;
    return type;
}