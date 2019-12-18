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
struct video_device {int dummy; } ;
struct qcam_device {int /*<<< orphan*/  in_use; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int qcam_exclusive_open(struct file *file)
{
	struct video_device *dev = video_devdata(file);
	struct qcam_device *qcam = (struct qcam_device *)dev;

	return test_and_set_bit(0, &qcam->in_use) ? -EBUSY : 0;
}