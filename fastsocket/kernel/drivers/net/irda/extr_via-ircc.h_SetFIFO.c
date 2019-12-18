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
 int /*<<< orphan*/  WriteRegBit (int,int,int,int) ; 

__attribute__((used)) static void SetFIFO(__u16 iobase, __u16 value)
{
	switch (value) {
	case 128:
		WriteRegBit(iobase, 0x11, 0, 0);
		WriteRegBit(iobase, 0x11, 7, 1);
		break;
	case 64:
		WriteRegBit(iobase, 0x11, 0, 0);
		WriteRegBit(iobase, 0x11, 7, 0);
		break;
	case 32:
		WriteRegBit(iobase, 0x11, 0, 1);
		WriteRegBit(iobase, 0x11, 7, 0);
		break;
	default:
		WriteRegBit(iobase, 0x11, 0, 0);
		WriteRegBit(iobase, 0x11, 7, 0);
	}

}