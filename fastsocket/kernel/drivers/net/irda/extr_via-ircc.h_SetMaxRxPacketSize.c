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
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  I_CF_H_2 ; 
 int /*<<< orphan*/  I_CF_L_2 ; 
 int /*<<< orphan*/  WriteReg (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SetMaxRxPacketSize(__u16 iobase, __u16 size)
{
	__u16 low, high;
	if ((size & 0xe000) == 0) {
		low = size & 0x00ff;
		high = (size & 0x1f00) >> 8;
		WriteReg(iobase, I_CF_L_2, low);
		WriteReg(iobase, I_CF_H_2, high);

	}

}