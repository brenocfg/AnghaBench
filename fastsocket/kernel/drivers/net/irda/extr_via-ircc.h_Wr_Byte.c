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
 int /*<<< orphan*/  ClkTx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Sdelay (int) ; 
 int /*<<< orphan*/  Tdelay (int) ; 

__attribute__((used)) static void Wr_Byte(__u16 iobase, __u8 data)
{
	__u8 bData = data;
//      __u8 btmp;
	int i;

	ClkTx(iobase, 0, 1);

	Tdelay(2);
	ActClk(iobase, 1);
	Tdelay(1);

	for (i = 0; i < 8; i++) {	//LDN

		if ((bData >> i) & 0x01) {
			ClkTx(iobase, 0, 1);	//bit data = 1;
		} else {
			ClkTx(iobase, 0, 0);	//bit data = 1;
		}
		Tdelay(2);
		Sdelay(1);
		ActClk(iobase, 1);	//clk hi
		Tdelay(1);
	}
}