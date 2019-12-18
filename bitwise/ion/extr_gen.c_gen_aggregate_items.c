#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ kind; int /*<<< orphan*/  base; int /*<<< orphan*/  num_elems; } ;
struct TYPE_7__ {size_t num_items; scalar_t__ kind; TYPE_1__* items; } ;
struct TYPE_6__ {scalar_t__ kind; size_t num_names; TYPE_2__* subaggregate; int /*<<< orphan*/ * names; TYPE_3__* type; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ AggregateItem ;
typedef  TYPE_2__ Aggregate ;

/* Variables and functions */
 scalar_t__ AGGREGATE_ITEM_FIELD ; 
 scalar_t__ AGGREGATE_ITEM_SUBAGGREGATE ; 
 scalar_t__ AGGREGATE_STRUCT ; 
 scalar_t__ TYPESPEC_ARRAY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_indent ; 
 int /*<<< orphan*/  gen_sync_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlnf (char*,...) ; 
 TYPE_3__* new_typespec_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typespec_to_cdecl (TYPE_3__*,int /*<<< orphan*/ ) ; 

void gen_aggregate_items(Aggregate *aggregate) {
    gen_indent++;
    for (size_t i = 0; i < aggregate->num_items; i++) {
        AggregateItem item = aggregate->items[i];
        if (item.kind == AGGREGATE_ITEM_FIELD) {
            for (size_t j = 0; j < item.num_names; j++) {
                gen_sync_pos(item.pos);
                if (item.type->kind == TYPESPEC_ARRAY && !item.type->num_elems) {
                    genlnf("%s;", typespec_to_cdecl(new_typespec_ptr(item.pos, item.type->base), item.names[j]));
                } else {
                    genlnf("%s;", typespec_to_cdecl(item.type, item.names[j]));
                }
            }
        } else if (item.kind == AGGREGATE_ITEM_SUBAGGREGATE) {
            genlnf("%s {", item.subaggregate->kind == AGGREGATE_STRUCT ? "struct" : "union");
            gen_aggregate_items(item.subaggregate);
            genlnf("};");
        } else {
            assert(0);
        }
    }
    gen_indent--;
}