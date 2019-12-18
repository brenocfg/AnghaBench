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
 int /*<<< orphan*/  DC ; 
 int OCD_DC_DBE_BIT ; 
 int OCD_DC_RES_BIT ; 
 int /*<<< orphan*/  ocd_write (int /*<<< orphan*/ ,int) ; 

void machine_restart(char *cmd)
{
	ocd_write(DC, (1 << OCD_DC_DBE_BIT));
	ocd_write(DC, (1 << OCD_DC_RES_BIT));
	while (1) ;
}