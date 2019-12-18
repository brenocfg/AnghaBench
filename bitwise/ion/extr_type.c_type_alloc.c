#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeKind ;
struct TYPE_5__ {scalar_t__ typeid; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 int /*<<< orphan*/  next_typeid ; 
 int /*<<< orphan*/  register_typeid (TYPE_1__*) ; 
 TYPE_1__* xcalloc (int,int) ; 

Type *type_alloc(TypeKind kind) {
    Type *type = xcalloc(1, sizeof(Type));
    type->kind = kind;
    type->typeid = next_typeid++;
    register_typeid(type);
    return type;
}