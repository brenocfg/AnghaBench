#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_3__ {struct saa7134_dev* dev; TYPE_2__ timeout; int /*<<< orphan*/  queue; } ;
struct saa7134_dev {TYPE_1__ vbi_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int VIDEO_MAX_FRAME ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  saa7134_buffer_timeout ; 
 int vbibufs ; 

int saa7134_vbi_init1(struct saa7134_dev *dev)
{
	INIT_LIST_HEAD(&dev->vbi_q.queue);
	init_timer(&dev->vbi_q.timeout);
	dev->vbi_q.timeout.function = saa7134_buffer_timeout;
	dev->vbi_q.timeout.data     = (unsigned long)(&dev->vbi_q);
	dev->vbi_q.dev              = dev;

	if (vbibufs < 2)
		vbibufs = 2;
	if (vbibufs > VIDEO_MAX_FRAME)
		vbibufs = VIDEO_MAX_FRAME;
	return 0;
}