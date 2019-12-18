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
struct maxiradio {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct maxiradio*,int,char*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power ; 

__attribute__((used)) static void turn_power(struct maxiradio *dev, int p)
{
	if (p != 0) {
		dprintk(dev, 1, "Radio powered on\n");
		outb(power, dev->io);
	} else {
		dprintk(dev, 1, "Radio powered off\n");
		outb(0, dev->io);
	}
}