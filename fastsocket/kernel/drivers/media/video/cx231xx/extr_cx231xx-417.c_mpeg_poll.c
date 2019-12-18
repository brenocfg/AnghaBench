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
struct poll_table_struct {int dummy; } ;
struct file {struct cx231xx_fh* private_data; } ;
struct cx231xx_fh {int /*<<< orphan*/  vidq; } ;

/* Variables and functions */
 unsigned int videobuf_poll_stream (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static unsigned int mpeg_poll(struct file *file,
	struct poll_table_struct *wait)
{
	struct cx231xx_fh *fh = file->private_data;
	/*struct cx231xx *dev = fh->dev;*/

	/*dprintk(2, "%s\n", __func__);*/

	return videobuf_poll_stream(file, &fh->vidq, wait);
}