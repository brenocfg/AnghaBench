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
struct snd_opl3 {int /*<<< orphan*/ * oss_seq_dev; } ;

/* Variables and functions */

void snd_opl3_free_seq_oss(struct snd_opl3 *opl3)
{
	if (opl3->oss_seq_dev) {
		/* The instance should have been released in prior */
		opl3->oss_seq_dev = NULL;
	}
}