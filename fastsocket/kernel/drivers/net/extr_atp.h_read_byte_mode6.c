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

/* Variables and functions */
 int HNib ; 
 int MAR ; 
 scalar_t__ PAR_DATA ; 
 scalar_t__ PAR_STATUS ; 
 int RdAddr ; 
 int inbyte (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static inline unsigned char read_byte_mode6(short ioaddr)
{
    unsigned char low_nib;

    outb(RdAddr | MAR, ioaddr + PAR_DATA);
    inbyte(ioaddr + PAR_STATUS);
    low_nib = (inbyte(ioaddr + PAR_STATUS) >> 3) & 0x0f;
    outb(RdAddr | HNib | MAR, ioaddr + PAR_DATA);
    inbyte(ioaddr + PAR_STATUS);
    return low_nib | ((inbyte(ioaddr + PAR_STATUS) << 1) & 0xf0);
}