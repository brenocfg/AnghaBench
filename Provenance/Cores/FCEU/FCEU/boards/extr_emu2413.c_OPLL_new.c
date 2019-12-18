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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {scalar_t__ mask; } ;
typedef  TYPE_1__ OPLL ;

/* Variables and functions */
 int /*<<< orphan*/  OPLL_reset (TYPE_1__*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  maketables (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

OPLL *OPLL_new(uint32 clk, uint32 rate) {
	OPLL *opll;

	maketables(clk, rate);

	opll = (OPLL*)calloc(sizeof(OPLL), 1);
	if (opll == NULL)
		return NULL;

	opll->mask = 0;

	OPLL_reset(opll);

	return opll;
}