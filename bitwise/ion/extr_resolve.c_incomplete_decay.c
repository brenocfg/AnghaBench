#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* base; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 scalar_t__ is_incomplete_array_type (TYPE_1__*) ; 
 scalar_t__ is_ptr_type (TYPE_1__*) ; 
 TYPE_1__* type_ptr (TYPE_1__*) ; 

Type *incomplete_decay(Type *type) {
    if (is_incomplete_array_type(type) || is_ptr_type(type)) {
        return type_ptr(incomplete_decay(type->base));
    } else {
        return type;
    }
}