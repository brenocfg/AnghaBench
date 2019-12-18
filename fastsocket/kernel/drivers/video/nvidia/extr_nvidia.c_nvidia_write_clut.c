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
typedef  int /*<<< orphan*/  u8 ;
struct nvidia_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVWriteDacData (struct nvidia_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteDacMask (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVWriteDacWriteAddr (struct nvidia_par*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvidia_write_clut(struct nvidia_par *par,
			      u8 regnum, u8 red, u8 green, u8 blue)
{
	NVWriteDacMask(par, 0xff);
	NVWriteDacWriteAddr(par, regnum);
	NVWriteDacData(par, red);
	NVWriteDacData(par, green);
	NVWriteDacData(par, blue);
}