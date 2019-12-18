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
 int /*<<< orphan*/  release_firmware (scalar_t__) ; 
 scalar_t__ sequencer_fw ; 

int asd_release_firmware(void)
{
	if (sequencer_fw)
		release_firmware(sequencer_fw);
	return 0;
}