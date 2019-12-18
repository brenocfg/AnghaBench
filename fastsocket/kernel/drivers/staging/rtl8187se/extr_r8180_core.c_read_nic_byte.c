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
struct net_device {scalar_t__ mem_start; } ;

/* Variables and functions */
 int readb (int*) ; 

u8 read_nic_byte(struct net_device *dev, int x)
{
        return 0xff&readb((u8*)dev->mem_start +x);
}