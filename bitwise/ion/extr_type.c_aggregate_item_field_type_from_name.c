#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;

/* Variables and functions */
 int aggregate_item_field_index (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * aggregate_item_field_type_from_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_aggregate_type (int /*<<< orphan*/ *) ; 

Type *aggregate_item_field_type_from_name(Type *type, const char *name) {
    assert(is_aggregate_type(type));
    int index = aggregate_item_field_index(type, name);
    if (index < 0) {
        return NULL;
    }
    return aggregate_item_field_type_from_index(type, index);
}