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
 int /*<<< orphan*/  FD_RECALIBRATE ; 
 int /*<<< orphan*/  LAST_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_drive ; 
 int /*<<< orphan*/  debugt (char*) ; 
 int /*<<< orphan*/  do_floppy ; 
 int /*<<< orphan*/  output_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recal_interrupt ; 

__attribute__((used)) static void recalibrate_floppy(void)
{
	debugt("recalibrate floppy:");
	do_floppy = recal_interrupt;
	output_byte(FD_RECALIBRATE);
	LAST_OUT(UNIT(current_drive));
}