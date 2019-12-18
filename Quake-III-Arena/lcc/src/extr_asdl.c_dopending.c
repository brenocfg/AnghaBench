#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rcc_symbol_ty ;
struct TYPE_2__ {int /*<<< orphan*/  items; } ;
typedef  int /*<<< orphan*/ * Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  Seq_addhi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pending ; 
 TYPE_1__* pickle ; 
 int /*<<< orphan*/  rcc_Symbol (int,int /*<<< orphan*/ ) ; 
 int symboluid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dopending(Symbol p) {
	if (pending != NULL) {
		int uid = symboluid(pending);
		rcc_symbol_ty symbol = mk_symbol(pending);
		Seq_addhi(pickle->items, rcc_Symbol(uid, symbol));
	}
	pending = p;
}