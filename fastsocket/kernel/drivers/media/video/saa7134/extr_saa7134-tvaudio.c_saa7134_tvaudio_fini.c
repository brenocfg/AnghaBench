#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ thread; int /*<<< orphan*/  stopped; } ;
struct saa7134_dev {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_ANALOG_IO_SELECT ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  saa_andorb (int /*<<< orphan*/ ,int,int) ; 

int saa7134_tvaudio_fini(struct saa7134_dev *dev)
{
	/* shutdown tvaudio thread */
	if (dev->thread.thread && !dev->thread.stopped)
		kthread_stop(dev->thread.thread);

	saa_andorb(SAA7134_ANALOG_IO_SELECT, 0x07, 0x00); /* LINE1 */
	return 0;
}