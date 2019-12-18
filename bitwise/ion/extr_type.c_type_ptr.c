#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* base; int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ Type ;
struct TYPE_11__ {int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t TYPE_PTR ; 
 int /*<<< orphan*/  cached_ptr_types ; 
 TYPE_1__* map_get (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* type_alloc (size_t) ; 
 TYPE_4__* type_metrics ; 

Type *type_ptr(Type *base) {
    Type *type = map_get(&cached_ptr_types, base);
    if (!type) {
        type = type_alloc(TYPE_PTR);
        type->size = type_metrics[TYPE_PTR].size;
        type->align = type_metrics[TYPE_PTR].align;
        type->base = base;
        map_put(&cached_ptr_types, base, type);
    }
    return type;
}