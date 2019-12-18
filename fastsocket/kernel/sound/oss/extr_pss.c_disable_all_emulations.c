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
 int /*<<< orphan*/  CONF_CDROM ; 
 int /*<<< orphan*/  CONF_MIDI ; 
 int /*<<< orphan*/  CONF_PSS ; 
 int /*<<< orphan*/  CONF_SB ; 
 int /*<<< orphan*/  CONF_WSS ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_all_emulations(void)
{
	outw(0x0000, REG(CONF_PSS));	/* 0x0400 enables joystick */
	outw(0x0000, REG(CONF_WSS));
	outw(0x0000, REG(CONF_SB));
	outw(0x0000, REG(CONF_MIDI));
	outw(0x0000, REG(CONF_CDROM));
}