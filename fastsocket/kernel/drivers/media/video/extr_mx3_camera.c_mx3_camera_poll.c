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
struct soc_camera_file {int /*<<< orphan*/  vb_vidq; } ;
struct file {struct soc_camera_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int videobuf_poll_stream (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int mx3_camera_poll(struct file *file, poll_table *pt)
{
	struct soc_camera_file *icf = file->private_data;

	return videobuf_poll_stream(file, &icf->vb_vidq, pt);
}