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
typedef  int u32 ;

/* Variables and functions */
 unsigned int AZX_MAX_CODECS ; 
 int /*<<< orphan*/  snd_BUG () ; 

__attribute__((used)) static unsigned int azx_command_addr(u32 cmd)
{
	unsigned int addr = cmd >> 28;

	if (addr >= AZX_MAX_CODECS) {
		snd_BUG();
		addr = 0;
	}

	return addr;
}