#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  seg; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_2__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  dopending (TYPE_2__*) ; 
 int /*<<< orphan*/  put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Global (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symboluid (TYPE_2__*) ; 

__attribute__((used)) static void asdl_global(Symbol p) {
	dopending(p);
	put(rcc_Global(symboluid(p), p->u.seg));
}