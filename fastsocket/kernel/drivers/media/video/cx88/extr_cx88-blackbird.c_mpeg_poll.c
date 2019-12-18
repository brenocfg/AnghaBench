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
struct file {struct cx8802_fh* private_data; } ;
struct cx8802_fh {int /*<<< orphan*/  mpegq; struct cx8802_dev* dev; } ;
struct cx8802_dev {int /*<<< orphan*/  mpeg_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  blackbird_start_codec (struct file*,struct cx8802_fh*) ; 
 unsigned int videobuf_poll_stream (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static unsigned int
mpeg_poll(struct file *file, struct poll_table_struct *wait)
{
	struct cx8802_fh *fh = file->private_data;
	struct cx8802_dev *dev = fh->dev;

	if (!dev->mpeg_active)
		blackbird_start_codec(file, fh);

	return videobuf_poll_stream(file, &fh->mpegq, wait);
}