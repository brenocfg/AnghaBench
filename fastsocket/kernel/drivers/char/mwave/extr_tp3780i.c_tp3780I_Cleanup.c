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
typedef  int /*<<< orphan*/  THINKPAD_BD_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  PRINTK_2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE_TP3780I ; 

int tp3780I_Cleanup(THINKPAD_BD_DATA * pBDData)
{
	int retval = 0;

	PRINTK_2(TRACE_TP3780I,
		"tp3780i::tp3780I_Cleanup entry and exit pBDData %p\n", pBDData);

	return retval;
}