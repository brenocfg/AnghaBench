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
typedef  scalar_t__ u32 ;
struct saa7164_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 scalar_t__ saa7164_readb (scalar_t__) ; 

void saa7164_dumpregs(struct saa7164_dev *dev, u32 addr)
{
	int i;

	dprintk(1, "--------------------> "
		"00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n");

	for (i = 0; i < 0x100; i += 16)
		dprintk(1, "region0[0x%08x] = "
			"%02x %02x %02x %02x %02x %02x %02x %02x"
			" %02x %02x %02x %02x %02x %02x %02x %02x\n", i,
			(u8)saa7164_readb(addr + i + 0),
			(u8)saa7164_readb(addr + i + 1),
			(u8)saa7164_readb(addr + i + 2),
			(u8)saa7164_readb(addr + i + 3),
			(u8)saa7164_readb(addr + i + 4),
			(u8)saa7164_readb(addr + i + 5),
			(u8)saa7164_readb(addr + i + 6),
			(u8)saa7164_readb(addr + i + 7),
			(u8)saa7164_readb(addr + i + 8),
			(u8)saa7164_readb(addr + i + 9),
			(u8)saa7164_readb(addr + i + 10),
			(u8)saa7164_readb(addr + i + 11),
			(u8)saa7164_readb(addr + i + 12),
			(u8)saa7164_readb(addr + i + 13),
			(u8)saa7164_readb(addr + i + 14),
			(u8)saa7164_readb(addr + i + 15)
			);
}