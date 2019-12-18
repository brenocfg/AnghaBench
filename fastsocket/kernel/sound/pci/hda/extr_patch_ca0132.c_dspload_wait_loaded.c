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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 scalar_t__ dspload_is_loaded (struct hda_codec*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static bool dspload_wait_loaded(struct hda_codec *codec)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(2000);

	do {
		if (dspload_is_loaded(codec)) {
			pr_info("ca0132 DOWNLOAD OK :-) DSP IS RUNNING.\n");
			return true;
		}
		msleep(20);
	} while (time_before(jiffies, timeout));

	pr_err("ca0132 DOWNLOAD FAILED!!! DSP IS NOT RUNNING.\n");
	return false;
}