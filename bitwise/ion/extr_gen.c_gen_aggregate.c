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
struct TYPE_4__ {scalar_t__ kind; int /*<<< orphan*/  aggregate; scalar_t__ is_incomplete; } ;
typedef  TYPE_1__ Decl ;

/* Variables and functions */
 scalar_t__ DECL_STRUCT ; 
 scalar_t__ DECL_UNION ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gen_aggregate_items (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlnf (char*,...) ; 
 int /*<<< orphan*/  get_gen_name (TYPE_1__*) ; 

void gen_aggregate(Decl *decl) {
    assert(decl->kind == DECL_STRUCT || decl->kind == DECL_UNION);
    if (decl->is_incomplete) {
        return;
    }
    genlnf("%s %s {", decl->kind == DECL_STRUCT ? "struct" : "union", get_gen_name(decl));
    gen_aggregate_items(decl->aggregate);
    genlnf("};");
}