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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  di_mite_ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  prealloc_bufsz; int /*<<< orphan*/  prealloc_buf; } ;

/* Variables and functions */
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mite_buf_change (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int ni_pcidio_change(struct comedi_device *dev,
			    struct comedi_subdevice *s, unsigned long new_size)
{
	int ret;

	ret = mite_buf_change(devpriv->di_mite_ring, s->async);
	if (ret < 0)
		return ret;

	memset(s->async->prealloc_buf, 0xaa, s->async->prealloc_bufsz);

	return 0;
}