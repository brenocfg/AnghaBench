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
 int /*<<< orphan*/  I_CF_H_0 ; 
 int /*<<< orphan*/  I_CF_L_0 ; 
 int ReadReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteRegBit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void SetFIR(__u16 BaseAddr, __u8 val)
{
	__u8 tmp;

	WriteRegBit(BaseAddr, I_CF_H_0, 5, 0);
	tmp = ReadReg(BaseAddr, I_CF_L_0);
	WriteReg(BaseAddr, I_CF_L_0, tmp & 0x8f);
	WriteRegBit(BaseAddr, I_CF_L_0, 6, val);
}