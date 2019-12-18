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
struct pluto {int dummy; } ;

/* Variables and functions */
 int MISC_FRST ; 
 int /*<<< orphan*/  REG_MISC ; 
 int pluto_readreg (struct pluto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_writereg (struct pluto*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pluto_reset_frontend(struct pluto *pluto, int reenable)
{
	u32 val = pluto_readreg(pluto, REG_MISC);

	if (val & MISC_FRST) {
		val &= ~MISC_FRST;
		pluto_writereg(pluto, REG_MISC, val);
	}
	if (reenable) {
		val |= MISC_FRST;
		pluto_writereg(pluto, REG_MISC, val);
	}
}