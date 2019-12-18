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
typedef  int /*<<< orphan*/  volatile u32 ;

/* Variables and functions */
 scalar_t__ io_p2v (int /*<<< orphan*/  volatile) ; 

__attribute__((used)) static __inline__ u32 usb_read(u32 port)
{
	return *(volatile u32 *)io_p2v(port);
}