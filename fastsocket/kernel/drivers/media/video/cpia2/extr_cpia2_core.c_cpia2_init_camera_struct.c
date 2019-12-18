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
struct camera_data {int present; int /*<<< orphan*/  wq_stream; int /*<<< orphan*/  busy_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct camera_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct camera_data *cpia2_init_camera_struct(void)
{
	struct camera_data *cam;

	cam = kzalloc(sizeof(*cam), GFP_KERNEL);

	if (!cam) {
		ERR("couldn't kmalloc cpia2 struct\n");
		return NULL;
	}


	cam->present = 1;
	mutex_init(&cam->busy_lock);
	init_waitqueue_head(&cam->wq_stream);

	return cam;
}