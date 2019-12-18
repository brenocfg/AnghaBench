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
 int /*<<< orphan*/  eprom_ck_cycle (struct net_device*) ; 
 int /*<<< orphan*/  eprom_w (struct net_device*,short) ; 

void eprom_send_bits_string(struct net_device *dev, short b[], int len)
{
	int i;

	for(i=0; i<len; i++){
		eprom_w(dev, b[i]);
		eprom_ck_cycle(dev);
	}
}