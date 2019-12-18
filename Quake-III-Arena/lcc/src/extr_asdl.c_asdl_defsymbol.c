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
struct TYPE_4__ {scalar_t__ scope; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 scalar_t__ GLOBAL ; 
 int /*<<< orphan*/  symboluid (TYPE_1__*) ; 

__attribute__((used)) static void asdl_defsymbol(Symbol p) {
	if (p->scope >= GLOBAL)
		symboluid(p);
}