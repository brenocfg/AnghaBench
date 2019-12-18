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
struct file {int dummy; } ;
struct audio_operations {int /*<<< orphan*/  poll_sleeper; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 struct audio_operations** audio_devs ; 
 unsigned int poll_input (struct file*,int,int /*<<< orphan*/ *) ; 
 unsigned int poll_output (struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

unsigned int DMAbuf_poll(struct file * file, int dev, poll_table *wait)
{
	struct audio_operations *adev = audio_devs[dev];
	poll_wait(file, &adev->poll_sleeper, wait);
	return poll_input(file, dev, wait) | poll_output(file, dev, wait);
}