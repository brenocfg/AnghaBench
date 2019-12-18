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
struct sn9c102_device {int /*<<< orphan*/  kref; TYPE_1__* v4ldev; int /*<<< orphan*/  wait_open; int /*<<< orphan*/  users; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn9c102_dev_lock ; 
 int /*<<< orphan*/  sn9c102_release_buffers (struct sn9c102_device*) ; 
 int /*<<< orphan*/  sn9c102_release_resources ; 
 int /*<<< orphan*/  sn9c102_stop_transfer (struct sn9c102_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct sn9c102_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  wake_up_interruptible_nr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sn9c102_release(struct file *filp)
{
	struct sn9c102_device* cam;

	down_write(&sn9c102_dev_lock);

	cam = video_drvdata(filp);

	sn9c102_stop_transfer(cam);
	sn9c102_release_buffers(cam);
	cam->users--;
	wake_up_interruptible_nr(&cam->wait_open, 1);

	DBG(3, "Video device /dev/video%d closed", cam->v4ldev->num);

	kref_put(&cam->kref, sn9c102_release_resources);

	up_write(&sn9c102_dev_lock);

	return 0;
}