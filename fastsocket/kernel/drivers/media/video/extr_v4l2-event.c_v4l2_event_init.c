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
struct v4l2_fh {TYPE_1__* events; } ;
struct TYPE_2__ {int sequence; int /*<<< orphan*/  subscribed; int /*<<< orphan*/  available; int /*<<< orphan*/  free; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 

int v4l2_event_init(struct v4l2_fh *fh)
{
	fh->events = kzalloc(sizeof(*fh->events), GFP_KERNEL);
	if (fh->events == NULL)
		return -ENOMEM;

	init_waitqueue_head(&fh->events->wait);

	INIT_LIST_HEAD(&fh->events->free);
	INIT_LIST_HEAD(&fh->events->available);
	INIT_LIST_HEAD(&fh->events->subscribed);

	fh->events->sequence = -1;

	return 0;
}