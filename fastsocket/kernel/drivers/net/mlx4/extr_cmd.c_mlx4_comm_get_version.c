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
 scalar_t__ CMD_CHAN_IF_REV ; 
 scalar_t__ CMD_CHAN_VER ; 

u32 mlx4_comm_get_version(void)
{
	 return ((u32) CMD_CHAN_IF_REV << 8) | (u32) CMD_CHAN_VER;
}