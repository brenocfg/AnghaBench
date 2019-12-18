#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* rcc_interface_ty ;
struct TYPE_11__ {int /*<<< orphan*/  i; } ;
typedef  TYPE_4__ Value ;
struct TYPE_12__ {int /*<<< orphan*/  (* defconst ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  suffix; int /*<<< orphan*/  value; } ;
struct TYPE_9__ {TYPE_1__ rcc_Defconst; } ;
struct TYPE_10__ {TYPE_2__ v; } ;

/* Variables and functions */
 TYPE_7__* IR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__) ; 

__attribute__((used)) static void doDefconst(rcc_interface_ty in) {
	Value v;

	v.i = in->v.rcc_Defconst.value;
	(*IR->defconst)(in->v.rcc_Defconst.suffix, in->v.rcc_Defconst.size, v);
}