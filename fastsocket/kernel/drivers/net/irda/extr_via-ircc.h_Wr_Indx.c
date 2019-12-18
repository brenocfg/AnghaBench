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
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ActClk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ClkTx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tdelay (int) ; 
 int /*<<< orphan*/  Wr_Byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void Wr_Indx(__u16 iobase, __u8 addr, __u8 index, __u8 data)
{
	int i;
	__u8 bTmp;

	ClkTx(iobase, 0, 0);
	udelay(2);
	ActClk(iobase, 1);
	udelay(1);
	bTmp = addr | (index << 1) | 1;
	Wr_Byte(iobase, bTmp);
	Wr_Byte(iobase, data);
	for (i = 0; i < 2; i++) {
		ClkTx(iobase, 0, 0);
		Tdelay(2);
		ActClk(iobase, 1);
		Tdelay(1);
	}
	ActClk(iobase, 0);
}