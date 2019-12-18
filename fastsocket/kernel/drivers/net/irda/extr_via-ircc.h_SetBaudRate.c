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
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  I_CF_H_1 ; 
 scalar_t__ IsFIROn (int /*<<< orphan*/ ) ; 
 scalar_t__ IsMIROn (int /*<<< orphan*/ ) ; 
 scalar_t__ IsSIROn (int /*<<< orphan*/ ) ; 
 int ReadReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SetBaudRate(__u16 iobase, __u32 rate)
{
	__u8 value = 11, temp;

	if (IsSIROn(iobase)) {
		switch (rate) {
		case (__u32) (2400L):
			value = 47;
			break;
		case (__u32) (9600L):
			value = 11;
			break;
		case (__u32) (19200L):
			value = 5;
			break;
		case (__u32) (38400L):
			value = 2;
			break;
		case (__u32) (57600L):
			value = 1;
			break;
		case (__u32) (115200L):
			value = 0;
			break;
		default:
			break;
		};
	} else if (IsMIROn(iobase)) {
		value = 0;	// will automatically be fixed in 1.152M
	} else if (IsFIROn(iobase)) {
		value = 0;	// will automatically be fixed in 4M
	}
	temp = (ReadReg(iobase, I_CF_H_1) & 0x03);
	temp |= value << 2;
	WriteReg(iobase, I_CF_H_1, temp);
}