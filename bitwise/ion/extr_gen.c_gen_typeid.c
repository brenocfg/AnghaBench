#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  typeid; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 int /*<<< orphan*/  genf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ is_excluded_typeinfo (TYPE_1__*) ; 
 int /*<<< orphan*/  type_to_cdecl (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  typeid_kind_name (TYPE_1__*) ; 

void gen_typeid(Type *type) {
    if (type->size == 0 || is_excluded_typeinfo(type)) {
        genf("TYPEID0(%d, %s)", type->typeid, typeid_kind_name(type));
    } else {
        genf("TYPEID(%d, %s, %s)", type->typeid, typeid_kind_name(type), type_to_cdecl(type, ""));
    }
}