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
typedef  unsigned char u8 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PORT ; 
 unsigned char HI_NIBBLE ; 
 int /*<<< orphan*/  STATUS_PORT ; 
 scalar_t__ inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 de600_read_byte(unsigned char type, struct net_device *dev)
{
	/* dev used by macros */
	u8 lo;
	outb_p((type), DATA_PORT);
	lo = ((unsigned char)inb(STATUS_PORT)) >> 4;
	outb_p((type) | HI_NIBBLE, DATA_PORT);
	return ((unsigned char)inb(STATUS_PORT) & (unsigned char)0xf0) | lo;
}