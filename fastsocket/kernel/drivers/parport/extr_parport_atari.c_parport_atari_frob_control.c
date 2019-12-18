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
struct parport {int dummy; } ;

/* Variables and functions */
 unsigned char parport_atari_read_control (struct parport*) ; 
 int /*<<< orphan*/  parport_atari_write_control (struct parport*,unsigned char) ; 

__attribute__((used)) static unsigned char
parport_atari_frob_control(struct parport *p, unsigned char mask,
			   unsigned char val)
{
	unsigned char old = parport_atari_read_control(p);
	parport_atari_write_control(p, (old & ~mask) ^ val);
	return old;
}