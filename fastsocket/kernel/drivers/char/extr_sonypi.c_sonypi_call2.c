#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  ioport1; int /*<<< orphan*/  ioport2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITERATIONS_LONG ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ sonypi_device ; 
 int /*<<< orphan*/  wait_on_command (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 sonypi_call2(u8 dev, u8 fn)
{
	u8 v1;

	wait_on_command(0, inb_p(sonypi_device.ioport2) & 2, ITERATIONS_LONG);
	outb(dev, sonypi_device.ioport2);
	wait_on_command(0, inb_p(sonypi_device.ioport2) & 2, ITERATIONS_LONG);
	outb(fn, sonypi_device.ioport1);
	v1 = inb_p(sonypi_device.ioport1);
	return v1;
}