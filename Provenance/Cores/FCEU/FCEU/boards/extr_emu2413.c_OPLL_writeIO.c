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
typedef  int uint32 ;
struct TYPE_4__ {int adr; } ;
typedef  TYPE_1__ OPLL ;

/* Variables and functions */
 int /*<<< orphan*/  OPLL_writeReg (TYPE_1__*,int,int) ; 

void OPLL_writeIO(OPLL * opll, uint32 adr, uint32 val) {
	if (adr & 1)
		OPLL_writeReg(opll, opll->adr, val);
	else
		opll->adr = val;
}