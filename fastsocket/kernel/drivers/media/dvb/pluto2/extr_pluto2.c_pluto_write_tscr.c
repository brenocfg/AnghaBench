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
 int /*<<< orphan*/  REG_TSCR ; 
 int TSCR_ADEF ; 
 int TS_DMA_PACKETS ; 
 int /*<<< orphan*/  pluto_writereg (struct pluto*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pluto_write_tscr(struct pluto *pluto, u32 val)
{
	/* set the number of packets */
	val &= ~TSCR_ADEF;
	val |= TS_DMA_PACKETS / 2;

	pluto_writereg(pluto, REG_TSCR, val);
}