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
struct videobuf_queue {int dummy; } ;
struct saa7146_vv {int dummy; } ;
struct saa7146_fh {struct videobuf_queue video_q; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct file {struct saa7146_fh* private_data; } ;

/* Variables and functions */
 scalar_t__ IS_CAPTURE_ACTIVE (struct saa7146_fh*) ; 
 scalar_t__ IS_OVERLAY_ACTIVE (struct saa7146_fh*) ; 
 int saa7146_stop_preview (struct saa7146_fh*) ; 
 int video_end (struct saa7146_fh*,struct file*) ; 
 int /*<<< orphan*/  videobuf_stop (struct videobuf_queue*) ; 

__attribute__((used)) static void video_close(struct saa7146_dev *dev, struct file *file)
{
	struct saa7146_fh *fh = file->private_data;
	struct saa7146_vv *vv = dev->vv_data;
	struct videobuf_queue *q = &fh->video_q;
	int err;

	if (IS_CAPTURE_ACTIVE(fh) != 0) {
		err = video_end(fh, file);
	} else if (IS_OVERLAY_ACTIVE(fh) != 0) {
		err = saa7146_stop_preview(fh);
	}

	videobuf_stop(q);

	/* hmm, why is this function declared void? */
	/* return err */
}