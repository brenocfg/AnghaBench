#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t kind; int /*<<< orphan*/  align; int /*<<< orphan*/  size; scalar_t__ typeid; } ;
typedef  TYPE_1__ Type ;
struct TYPE_6__ {int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  next_typeid ; 
 int /*<<< orphan*/  register_typeid (TYPE_1__*) ; 
 TYPE_2__* type_metrics ; 

void init_builtin_type(Type *type) {
    type->typeid = next_typeid++;
    register_typeid(type);
    type->size = type_metrics[type->kind].size;
    type->align = type_metrics[type->kind].align;
}