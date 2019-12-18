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
struct net_device {struct adapter* ml_priv; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EEPROM_SIZE ; 
 scalar_t__ t1_is_asic (struct adapter*) ; 

__attribute__((used)) static int get_eeprom_len(struct net_device *dev)
{
	struct adapter *adapter = dev->ml_priv;

	return t1_is_asic(adapter) ? EEPROM_SIZE : 0;
}