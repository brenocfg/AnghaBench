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
 int ENODEV ; 
 int GPMC_CS_NUM ; 
 int gpmc_cs_map ; 

int gpmc_cs_reserved(int cs)
{
	if (cs > GPMC_CS_NUM)
		return -ENODEV;

	return gpmc_cs_map & (1 << cs);
}