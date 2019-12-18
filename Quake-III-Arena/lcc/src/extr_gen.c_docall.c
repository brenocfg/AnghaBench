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
struct TYPE_3__ {int /*<<< orphan*/ * syms; } ;
typedef  TYPE_1__* Node ;

/* Variables and functions */
 scalar_t__ argoffset ; 
 int /*<<< orphan*/  intconst (scalar_t__) ; 
 scalar_t__ maxargoffset ; 

__attribute__((used)) static void docall(Node p) {
	p->syms[1] = p->syms[0];
	p->syms[0] = intconst(argoffset);
	if (argoffset > maxargoffset)
		maxargoffset = argoffset;
	argoffset = 0;
}