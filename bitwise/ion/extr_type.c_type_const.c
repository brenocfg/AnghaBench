#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ kind; int nonmodifiable; struct TYPE_10__* base; int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 scalar_t__ TYPE_CONST ; 
 int /*<<< orphan*/  cached_const_types ; 
 int /*<<< orphan*/  complete_type (TYPE_1__*) ; 
 TYPE_1__* map_get (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* type_alloc (scalar_t__) ; 

Type *type_const(Type *base) {
    if (base->kind == TYPE_CONST) {
        return base;
    }
    Type *type = map_get(&cached_const_types, base);
    if (!type) {
        complete_type(base);
        type = type_alloc(TYPE_CONST);
        type->nonmodifiable = true;
        type->size = base->size;
        type->align = base->align;
        type->base = base;
        map_put(&cached_const_types, base, type);
    }
    return type;
}