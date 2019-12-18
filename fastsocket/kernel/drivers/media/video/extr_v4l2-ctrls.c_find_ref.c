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
typedef  int u32 ;
struct v4l2_ctrl_ref {struct v4l2_ctrl_ref* next; TYPE_1__* ctrl; } ;
struct v4l2_ctrl_handler {int nr_of_buckets; struct v4l2_ctrl_ref* cached; struct v4l2_ctrl_ref** buckets; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int V4L2_CID_PRIVATE_BASE ; 
 int V4L2_CTRL_ID_MASK ; 
 struct v4l2_ctrl_ref* find_private_ref (struct v4l2_ctrl_handler*,int) ; 

__attribute__((used)) static struct v4l2_ctrl_ref *find_ref(struct v4l2_ctrl_handler *hdl, u32 id)
{
	struct v4l2_ctrl_ref *ref;
	int bucket;

	id &= V4L2_CTRL_ID_MASK;

	/* Old-style private controls need special handling */
	if (id >= V4L2_CID_PRIVATE_BASE)
		return find_private_ref(hdl, id);
	bucket = id % hdl->nr_of_buckets;

	/* Simple optimization: cache the last control found */
	if (hdl->cached && hdl->cached->ctrl->id == id)
		return hdl->cached;

	/* Not in cache, search the hash */
	ref = hdl->buckets ? hdl->buckets[bucket] : NULL;
	while (ref && ref->ctrl->id != id)
		ref = ref->next;

	if (ref)
		hdl->cached = ref; /* cache it! */
	return ref;
}