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
struct hda_codec {int jackpoll_interval; } ;

/* Variables and functions */
 int msecs_to_jiffies (int) ; 
 int via_build_controls (struct hda_codec*) ; 

__attribute__((used)) static int vt1708_build_controls(struct hda_codec *codec)
{
	/* In order not to create "Phantom Jack" controls,
	   temporary enable jackpoll */
	int err;
	int old_interval = codec->jackpoll_interval;
	codec->jackpoll_interval = msecs_to_jiffies(100);
	err = via_build_controls(codec);
	codec->jackpoll_interval = old_interval;
	return err;
}