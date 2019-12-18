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
 unsigned char bit (int) ; 
 int /*<<< orphan*/  ks0108_delay ; 
 int /*<<< orphan*/  ks0108_parport ; 
 int /*<<< orphan*/  parport_write_control (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

void ks0108_writecontrol(unsigned char byte)
{
	udelay(ks0108_delay);
	parport_write_control(ks0108_parport, byte ^ (bit(0) | bit(1) | bit(3)));
}