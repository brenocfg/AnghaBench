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
struct TYPE_3__ {struct saa7146_dev* dev; TYPE_2__ timeout; int /*<<< orphan*/  queue; } ;
struct saa7146_vv {int /*<<< orphan*/  vbi_wq; TYPE_1__ vbi_q; } ;
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_VBI (char*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7146_buffer_timeout ; 

__attribute__((used)) static void vbi_init(struct saa7146_dev *dev, struct saa7146_vv *vv)
{
	DEB_VBI(("dev:%p\n",dev));

	INIT_LIST_HEAD(&vv->vbi_q.queue);

	init_timer(&vv->vbi_q.timeout);
	vv->vbi_q.timeout.function = saa7146_buffer_timeout;
	vv->vbi_q.timeout.data     = (unsigned long)(&vv->vbi_q);
	vv->vbi_q.dev              = dev;

	init_waitqueue_head(&vv->vbi_wq);
}