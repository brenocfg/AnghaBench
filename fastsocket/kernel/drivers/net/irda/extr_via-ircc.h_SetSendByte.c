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
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  TX_C_H ; 
 int /*<<< orphan*/  TX_C_L ; 
 int /*<<< orphan*/  WriteReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SetSendByte(__u16 iobase, __u32 count)
{
	__u32 low, high;

	if ((count & 0xf000) == 0) {
		low = count & 0x00ff;
		high = (count & 0x0f00) >> 8;
		WriteReg(iobase, TX_C_L, low);
		WriteReg(iobase, TX_C_H, high);
	}
}