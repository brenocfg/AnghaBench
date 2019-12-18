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
 int ANTIC_CHACTL ; 
 int ANTIC_CHBASE ; 
 int ANTIC_DMACTL ; 
 int ANTIC_GetByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ANTIC_HSCROL ; 
 int ANTIC_NMIEN ; 
 int /*<<< orphan*/  ANTIC_OFFSET_VCOUNT ; 
 int ANTIC_PMBASE ; 
 int ANTIC_VSCROL ; 
 int ANTIC_dlist ; 
 int ANTIC_ypos ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,...) ; 

__attribute__((used)) static void show_ANTIC(void)
{
	printf("DMACTL=%02X    CHACTL=%02X    DLISTL=%02X    "
		   "DLISTH=%02X    HSCROL=%02X    VSCROL=%02X\n",
		   ANTIC_DMACTL, ANTIC_CHACTL, ANTIC_dlist & 0xff, ANTIC_dlist >> 8, ANTIC_HSCROL, ANTIC_VSCROL);
	printf("PMBASE=%02X    CHBASE=%02X    VCOUNT=%02X    "
		   "NMIEN= %02X    ypos=%4d\n",
		   ANTIC_PMBASE, ANTIC_CHBASE, ANTIC_GetByte(ANTIC_OFFSET_VCOUNT, TRUE), ANTIC_NMIEN, ANTIC_ypos);
}