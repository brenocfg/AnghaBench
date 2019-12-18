#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* sym; } ;
typedef  TYPE_2__ Type ;
struct TYPE_7__ {int /*<<< orphan*/  decl; } ;
typedef  int /*<<< orphan*/  Aggregate ;

/* Variables and functions */
 TYPE_2__* complete_aggregate_strict (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_decl_foreign (int /*<<< orphan*/ ) ; 

Type *complete_aggregate(Type *type, Aggregate *aggregate) {
    return complete_aggregate_strict(type, aggregate, type->sym && is_decl_foreign(type->sym->decl));
}