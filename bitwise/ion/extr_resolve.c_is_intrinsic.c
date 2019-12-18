#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int intrinsic; } ;
struct TYPE_7__ {TYPE_1__ func; } ;
struct TYPE_6__ {scalar_t__ kind; TYPE_4__* type; } ;
typedef  TYPE_2__ Sym ;

/* Variables and functions */
 scalar_t__ SYM_FUNC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_func_type (TYPE_4__*) ; 

bool is_intrinsic(Sym *sym) {
    if (!sym || sym->kind != SYM_FUNC) {
        return false;
    }
    assert(is_func_type(sym->type));
    return sym->type->func.intrinsic;
}