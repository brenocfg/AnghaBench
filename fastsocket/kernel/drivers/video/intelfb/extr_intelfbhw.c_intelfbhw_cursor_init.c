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
typedef  int u32 ;
struct TYPE_2__ {int physical; int offset; } ;
struct intelfb_info {TYPE_1__ cursor; scalar_t__ mobile; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_A_BASEADDR ; 
 int /*<<< orphan*/  CURSOR_A_CONTROL ; 
 int /*<<< orphan*/  CURSOR_CONTROL ; 
 int CURSOR_ENABLE ; 
 int CURSOR_FORMAT_3C ; 
 int CURSOR_FORMAT_MASK ; 
 int CURSOR_GAMMA_ENABLE ; 
 int CURSOR_MEM_TYPE_LOCAL ; 
 int CURSOR_MOBILE_GAMMA_ENABLE ; 
 int CURSOR_MODE_DISABLE ; 
 int CURSOR_MODE_MASK ; 
 int CURSOR_PIPE_SELECT_SHIFT ; 
 int /*<<< orphan*/  CURSOR_SIZE ; 
 int CURSOR_SIZE_H_SHIFT ; 
 int CURSOR_SIZE_V_SHIFT ; 
 int CURSOR_STRIDE_MASK ; 
 int /*<<< orphan*/  DBG_MSG (char*) ; 
 int INREG (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_I9XX (struct intelfb_info*) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 

void intelfbhw_cursor_init(struct intelfb_info *dinfo)
{
	u32 tmp;

#if VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_init\n");
#endif

	if (dinfo->mobile || IS_I9XX(dinfo)) {
		if (!dinfo->cursor.physical)
			return;
		tmp = INREG(CURSOR_A_CONTROL);
		tmp &= ~(CURSOR_MODE_MASK | CURSOR_MOBILE_GAMMA_ENABLE |
			 CURSOR_MEM_TYPE_LOCAL |
			 (1 << CURSOR_PIPE_SELECT_SHIFT));
		tmp |= CURSOR_MODE_DISABLE;
		OUTREG(CURSOR_A_CONTROL, tmp);
		OUTREG(CURSOR_A_BASEADDR, dinfo->cursor.physical);
	} else {
		tmp = INREG(CURSOR_CONTROL);
		tmp &= ~(CURSOR_FORMAT_MASK | CURSOR_GAMMA_ENABLE |
			 CURSOR_ENABLE | CURSOR_STRIDE_MASK);
		tmp = CURSOR_FORMAT_3C;
		OUTREG(CURSOR_CONTROL, tmp);
		OUTREG(CURSOR_A_BASEADDR, dinfo->cursor.offset << 12);
		tmp = (64 << CURSOR_SIZE_H_SHIFT) |
		      (64 << CURSOR_SIZE_V_SHIFT);
		OUTREG(CURSOR_SIZE, tmp);
	}
}