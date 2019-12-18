#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ length; } ;
struct carlu {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_EEPROM_START ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENODATA ; 
 int carlu_cmd_mem_dump (struct carlu*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ cpu_to_le16 (int) ; 

int carlu_cmd_read_eeprom(struct carlu *ar)
{

	int err;

	err = carlu_cmd_mem_dump(ar, AR9170_EEPROM_START, sizeof(ar->eeprom),
				  &ar->eeprom);

#ifndef __CHECKER__
	/* don't want to handle trailing remains */
	BUILD_BUG_ON(sizeof(ar->eeprom) % 8);
#endif

	if (ar->eeprom.length == cpu_to_le16(0xffff))
		return -ENODATA;

	return 0;
}