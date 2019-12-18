#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct ti_ohci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*,int,int) ; 
 int reg_read (struct ti_ohci*,int) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int,int) ; 

__attribute__((used)) static int get_nb_iso_ctx(struct ti_ohci *ohci, int reg)
{
	int i,ctx=0;
	u32 tmp;

	reg_write(ohci, reg, 0xffffffff);
	tmp = reg_read(ohci, reg);

	DBGMSG("Iso contexts reg: %08x implemented: %08x", reg, tmp);

	/* Count the number of contexts */
	for (i=0; i<32; i++) {
	    	if (tmp & 1) ctx++;
		tmp >>= 1;
	}
	return ctx;
}