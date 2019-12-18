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
 int COPR_MIDI ; 
 int EIO ; 
 int /*<<< orphan*/  devc ; 
 int /*<<< orphan*/  set_mt32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_mpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sscape_coproc_open(void *dev_info, int sub_device)
{
	if (sub_device == COPR_MIDI)
	{
		set_mt32(devc, 0);
		if (!verify_mpu(devc))
			return -EIO;
	}
	return 0;
}