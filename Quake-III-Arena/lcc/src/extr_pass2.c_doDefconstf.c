#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* rcc_interface_ty ;
struct TYPE_12__ {int /*<<< orphan*/  d; } ;
typedef  TYPE_4__ Value ;
struct TYPE_14__ {int /*<<< orphan*/  (* defconst ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__) ;} ;
struct TYPE_13__ {unsigned int msb; unsigned int lsb; } ;
struct TYPE_10__ {TYPE_6__* value; int /*<<< orphan*/  size; } ;
struct TYPE_9__ {TYPE_2__ rcc_Defconstf; } ;
struct TYPE_11__ {TYPE_1__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  F ; 
 TYPE_8__* IR ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__) ; 
 size_t swap ; 

__attribute__((used)) static void doDefconstf(rcc_interface_ty in) {
	Value v;
	unsigned *p = (unsigned *)&v.d;

	p[swap]   = in->v.rcc_Defconstf.value->msb;
	p[1-swap] = in->v.rcc_Defconstf.value->lsb;
	(*IR->defconst)(F, in->v.rcc_Defconstf.size, v);
	free(in->v.rcc_Defconstf.value);
}