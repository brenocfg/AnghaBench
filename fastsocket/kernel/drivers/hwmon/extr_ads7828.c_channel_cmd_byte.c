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
typedef  int u8 ;

/* Variables and functions */
 int ads7828_cmd_byte ; 

__attribute__((used)) static inline u8 channel_cmd_byte(int ch)
{
	/* cmd byte C2,C1,C0 - see datasheet */
	u8 cmd = (((ch>>1) | (ch&0x01)<<2)<<4);
	cmd |= ads7828_cmd_byte;
	return cmd;
}