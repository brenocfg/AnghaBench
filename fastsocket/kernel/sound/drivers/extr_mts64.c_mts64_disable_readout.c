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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTS64_CTL_READOUT ; 
 int /*<<< orphan*/  parport_read_control (struct parport*) ; 
 int /*<<< orphan*/  parport_write_control (struct parport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mts64_disable_readout(struct parport *p)
{
	u8 c;

	c = parport_read_control(p);
	c &= ~MTS64_CTL_READOUT;
	parport_write_control(p, c);
}