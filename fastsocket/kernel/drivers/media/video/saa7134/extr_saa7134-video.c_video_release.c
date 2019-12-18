#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct saa7134_fh* read_buf; } ;
struct saa7134_fh {int /*<<< orphan*/  prio; int /*<<< orphan*/  pt_vbi; int /*<<< orphan*/  pt_cap; TYPE_1__ vbi; TYPE_1__ cap; scalar_t__ radio; struct saa7134_dev* dev; } ;
struct saa7134_dev {int /*<<< orphan*/  prio; int /*<<< orphan*/  pci; int /*<<< orphan*/  slock; } ;
struct saa6588_command {int dummy; } ;
struct file {struct saa7134_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  RESOURCE_VBI ; 
 int /*<<< orphan*/  RESOURCE_VIDEO ; 
 int /*<<< orphan*/  SAA6588_CMD_CLOSE ; 
 int /*<<< orphan*/  SAA7134_OFMT_DATA_A ; 
 int /*<<< orphan*/  SAA7134_OFMT_DATA_B ; 
 int /*<<< orphan*/  SAA7134_OFMT_VIDEO_A ; 
 int /*<<< orphan*/  SAA7134_OFMT_VIDEO_B ; 
 int /*<<< orphan*/  buffer_release (TYPE_1__*,struct saa7134_fh*) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  ioctl ; 
 int /*<<< orphan*/  kfree (struct saa7134_fh*) ; 
 scalar_t__ res_check (struct saa7134_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free (struct saa7134_dev*,struct saa7134_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  saa7134_pgtable_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa_andorb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_preview (struct saa7134_dev*,struct saa7134_fh*) ; 
 int /*<<< orphan*/  v4l2_prio_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videobuf_mmap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_streamoff (TYPE_1__*) ; 

__attribute__((used)) static int video_release(struct file *file)
{
	struct saa7134_fh  *fh  = file->private_data;
	struct saa7134_dev *dev = fh->dev;
	struct saa6588_command cmd;
	unsigned long flags;

	/* turn off overlay */
	if (res_check(fh, RESOURCE_OVERLAY)) {
		spin_lock_irqsave(&dev->slock,flags);
		stop_preview(dev,fh);
		spin_unlock_irqrestore(&dev->slock,flags);
		res_free(dev,fh,RESOURCE_OVERLAY);
	}

	/* stop video capture */
	if (res_check(fh, RESOURCE_VIDEO)) {
		videobuf_streamoff(&fh->cap);
		res_free(dev,fh,RESOURCE_VIDEO);
	}
	if (fh->cap.read_buf) {
		buffer_release(&fh->cap,fh->cap.read_buf);
		kfree(fh->cap.read_buf);
	}

	/* stop vbi capture */
	if (res_check(fh, RESOURCE_VBI)) {
		videobuf_stop(&fh->vbi);
		res_free(dev,fh,RESOURCE_VBI);
	}

	/* ts-capture will not work in planar mode, so turn it off Hac: 04.05*/
	saa_andorb(SAA7134_OFMT_VIDEO_A, 0x1f, 0);
	saa_andorb(SAA7134_OFMT_VIDEO_B, 0x1f, 0);
	saa_andorb(SAA7134_OFMT_DATA_A, 0x1f, 0);
	saa_andorb(SAA7134_OFMT_DATA_B, 0x1f, 0);

	saa_call_all(dev, core, s_power, 0);
	if (fh->radio)
		saa_call_all(dev, core, ioctl, SAA6588_CMD_CLOSE, &cmd);

	/* free stuff */
	videobuf_mmap_free(&fh->cap);
	videobuf_mmap_free(&fh->vbi);
	saa7134_pgtable_free(dev->pci,&fh->pt_cap);
	saa7134_pgtable_free(dev->pci,&fh->pt_vbi);

	v4l2_prio_close(&dev->prio, fh->prio);
	file->private_data = NULL;
	kfree(fh);
	return 0;
}