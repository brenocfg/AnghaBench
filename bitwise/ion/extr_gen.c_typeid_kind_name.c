#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t kind; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 size_t NUM_TYPE_KINDS ; 
 char** typeid_kind_names ; 

const char *typeid_kind_name(Type *type) {
    if (type->kind < NUM_TYPE_KINDS) {
        const char *name = typeid_kind_names[type->kind];
        if (name) {
            return name;
        }
    }
    return "TYPE_NONE";
}