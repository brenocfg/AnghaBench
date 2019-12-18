#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  label; } ;
struct TYPE_7__ {TYPE_1__ l; } ;
struct TYPE_8__ {scalar_t__ scope; TYPE_2__ u; } ;
typedef  TYPE_3__* Symbol ;

/* Variables and functions */
 scalar_t__ LABELS ; 
 int /*<<< orphan*/  put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Defaddress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Deflabel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symboluid (TYPE_3__*) ; 

__attribute__((used)) static void asdl_defaddress(Symbol p) {
	if (p->scope == LABELS)
		put(rcc_Deflabel(p->u.l.label));
	else
		put(rcc_Defaddress(symboluid(p)));
}