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
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_char ;
struct sym_device {int dummy; } ;
typedef  int /*<<< orphan*/  Tekram_nvram ;

/* Variables and functions */
 int INB (struct sym_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (struct sym_device*,int /*<<< orphan*/ ,int) ; 
 int T93C46_Read_Data (struct sym_device*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  nc_gpcntl ; 
 int /*<<< orphan*/  nc_gpreg ; 

__attribute__((used)) static int sym_read_T93C46_nvram(struct sym_device *np, Tekram_nvram *nvram)
{
	u_char gpcntl, gpreg;
	u_char old_gpcntl, old_gpreg;
	int retv = 1;

	/* save current state of GPCNTL and GPREG */
	old_gpreg	= INB(np, nc_gpreg);
	old_gpcntl	= INB(np, nc_gpcntl);

	/* set up GPREG & GPCNTL to set GPIO0/1/2/4 in to known state, 0 in,
	   1/2/4 out */
	gpreg = old_gpreg & 0xe9;
	OUTB(np, nc_gpreg, gpreg);
	gpcntl = (old_gpcntl & 0xe9) | 0x09;
	OUTB(np, nc_gpcntl, gpcntl);

	/* input all of NVRAM, 64 words */
	retv = T93C46_Read_Data(np, (u_short *) nvram,
				sizeof(*nvram) / sizeof(short), &gpreg);
	
	/* return GPIO0/1/2/4 to original states after having accessed NVRAM */
	OUTB(np, nc_gpcntl, old_gpcntl);
	OUTB(np, nc_gpreg,  old_gpreg);

	return retv;
}