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
struct r10conf {struct mddev* mddev; } ;
struct mddev {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unplug_slaves (struct mddev*) ; 

void md_raid10_unplug_device(struct r10conf *conf)
{
	struct mddev *mddev = conf->mddev;

	unplug_slaves(mddev);
	md_wakeup_thread(mddev->thread);
}