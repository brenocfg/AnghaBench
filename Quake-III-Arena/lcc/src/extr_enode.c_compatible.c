#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ eqtype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ isptr (TYPE_1__*) ; 
 int /*<<< orphan*/  unqual (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compatible(Type ty1, Type ty2) {
	return isptr(ty1) && !isfunc(ty1->type)
	    && isptr(ty2) && !isfunc(ty2->type)
	    && eqtype(unqual(ty1->type), unqual(ty2->type), 0);
}