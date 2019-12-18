#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ offset; } ;
struct TYPE_8__ {TYPE_1__ x; } ;
typedef  TYPE_2__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mk_symbol (TYPE_2__*) ; 
 int /*<<< orphan*/  put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  symboluid (TYPE_2__*) ; 

__attribute__((used)) static void asdl_address(Symbol q, Symbol p, long n) {
	assert(q->x.offset == 0);
	put(rcc_Address(symboluid(q), mk_symbol(q), symboluid(p), n));
}