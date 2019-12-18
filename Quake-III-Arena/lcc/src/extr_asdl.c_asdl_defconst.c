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
struct TYPE_4__ {unsigned long i; unsigned long u; scalar_t__ p; } ;
typedef  TYPE_1__ Value ;

/* Variables and functions */
#define  F 131 
#define  I 130 
#define  P 129 
#define  U 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_real (int,TYPE_1__) ; 
 int /*<<< orphan*/  put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Defconst (int,int,unsigned long) ; 
 int /*<<< orphan*/  rcc_Defconstf (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asdl_defconst(int suffix, int size, Value v) {
	switch (suffix) {
	case I: put(rcc_Defconst(suffix, size, v.i)); return;
	case U: put(rcc_Defconst(suffix, size, v.u)); return;
	case P: put(rcc_Defconst(suffix, size, (unsigned long)v.p)); return;	/* FIXME */
	case F: put(rcc_Defconstf(size, mk_real(size, v))); return;
	assert(0);
	}
}