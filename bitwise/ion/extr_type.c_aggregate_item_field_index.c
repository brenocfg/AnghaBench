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
struct TYPE_7__ {size_t num_fields; TYPE_1__* fields; } ;
struct TYPE_8__ {TYPE_2__ aggregate; } ;
typedef  TYPE_3__ Type ;
struct TYPE_6__ {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_aggregate_type (TYPE_3__*) ; 

int aggregate_item_field_index(Type *type, const char *name) {
    assert(is_aggregate_type(type));
    for (size_t i = 0; i < type->aggregate.num_fields; i++) {
        if (type->aggregate.fields[i].name == name) {
            return (int)i;
        }
    }
    return -1;
}