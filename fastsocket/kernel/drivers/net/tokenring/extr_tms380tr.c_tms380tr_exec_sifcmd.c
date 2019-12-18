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
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int CMD_INTERRUPT_ADAPTER ; 
 unsigned int CMD_SYSTEM_IRQ ; 
 int /*<<< orphan*/  SIFCMD ; 
 unsigned short SIFREADW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIFSTS ; 
 int /*<<< orphan*/  SIFWRITEW (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tms380tr_exec_sifcmd(struct net_device *dev, unsigned int WriteValue)
{
	unsigned short cmd;
	unsigned short SifStsValue;
	unsigned long loop_counter;

	WriteValue = ((WriteValue ^ CMD_SYSTEM_IRQ) | CMD_INTERRUPT_ADAPTER);
	cmd = (unsigned short)WriteValue;
	loop_counter = 0,5 * 800000;
	do {
		SifStsValue = SIFREADW(SIFSTS);
	} while((SifStsValue & CMD_INTERRUPT_ADAPTER) && loop_counter--);
	SIFWRITEW(cmd, SIFCMD);

	return;
}