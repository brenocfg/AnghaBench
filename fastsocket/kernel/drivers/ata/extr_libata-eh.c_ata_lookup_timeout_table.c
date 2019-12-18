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
typedef  scalar_t__ const u8 ;
struct TYPE_2__ {scalar_t__* commands; } ;

/* Variables and functions */
 int ATA_EH_CMD_TIMEOUT_TABLE_SIZE ; 
 TYPE_1__* ata_eh_cmd_timeout_table ; 

__attribute__((used)) static int ata_lookup_timeout_table(u8 cmd)
{
	int i;

	for (i = 0; i < ATA_EH_CMD_TIMEOUT_TABLE_SIZE; i++) {
		const u8 *cur;

		for (cur = ata_eh_cmd_timeout_table[i].commands; *cur; cur++)
			if (*cur == cmd)
				return i;
	}

	return -1;
}