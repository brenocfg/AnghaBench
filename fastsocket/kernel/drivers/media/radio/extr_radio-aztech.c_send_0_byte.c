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
struct aztech {int /*<<< orphan*/  io; int /*<<< orphan*/  curvol; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radio_wait_time ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 scalar_t__ volconvert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_0_byte(struct aztech *az)
{
	udelay(radio_wait_time);
	outb_p(2 + volconvert(az->curvol), az->io);
	outb_p(64 + 2 + volconvert(az->curvol), az->io);
}