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
struct via_ircc_cb {int dummy; } ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  RX_P_H ; 
 int /*<<< orphan*/  RX_P_L ; 
 int ReadReg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u16 RxCurCount(__u16 iobase, struct via_ircc_cb * self)
{
	__u8 low, high;
	__u16 wTmp = 0, wTmp1 = 0;

	low = ReadReg(iobase, RX_P_L);
	high = ReadReg(iobase, RX_P_H);
	wTmp1 = high;
	wTmp = (wTmp1 << 8) | low;
	return wTmp;
}