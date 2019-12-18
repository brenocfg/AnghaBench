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
struct TYPE_4__ {size_t num_items; int /*<<< orphan*/  items; int /*<<< orphan*/  kind; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  AggregateKind ;
typedef  int /*<<< orphan*/  AggregateItem ;
typedef  TYPE_1__ Aggregate ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DUP (int /*<<< orphan*/ *) ; 
 TYPE_1__* ast_alloc (int) ; 

Aggregate *new_aggregate(SrcPos pos, AggregateKind kind, AggregateItem *items, size_t num_items) {
    Aggregate *aggregate = ast_alloc(sizeof(Aggregate));
    aggregate->pos = pos;
    aggregate->kind = kind;
    aggregate->items = AST_DUP(items);
    aggregate->num_items = num_items;
    return aggregate;
}