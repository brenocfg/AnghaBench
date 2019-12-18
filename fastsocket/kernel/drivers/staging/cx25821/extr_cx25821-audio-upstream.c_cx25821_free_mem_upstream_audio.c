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
struct cx25821_dev {scalar_t__ _audio_is_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25821_free_memory_audio (struct cx25821_dev*) ; 
 int /*<<< orphan*/  cx25821_stop_upstream_audio (struct cx25821_dev*) ; 

void cx25821_free_mem_upstream_audio(struct cx25821_dev *dev)
{
	if (dev->_audio_is_running) {
		cx25821_stop_upstream_audio(dev);
	}

	cx25821_free_memory_audio(dev);
}