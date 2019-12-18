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
typedef  int volatile u32 ;

/* Variables and functions */
 scalar_t__ io_p2v (int volatile) ; 

__attribute__((used)) static __inline__ void usb_clear(u32 val, u32 port)
{
	volatile u32 *ioport = (volatile u32 *)io_p2v(port);
	u32 after = (*ioport) & ~val;
	*ioport = after;
}