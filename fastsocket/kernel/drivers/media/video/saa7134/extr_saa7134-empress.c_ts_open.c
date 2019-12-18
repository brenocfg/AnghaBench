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
struct video_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vb_lock; } ;
struct saa7134_dev {TYPE_1__ empress_tsq; int /*<<< orphan*/  empress_users; } ;
struct file {struct saa7134_dev* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SAA7134_AUDIO_MUTE_CTRL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int ts_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct saa7134_dev *dev = video_drvdata(file);
	int err;

	dprintk("open dev=%s\n", video_device_node_name(vdev));
	err = -EBUSY;
	if (!mutex_trylock(&dev->empress_tsq.vb_lock))
		return err;
	if (atomic_read(&dev->empress_users))
		goto done;

	/* Unmute audio */
	saa_writeb(SAA7134_AUDIO_MUTE_CTRL,
		saa_readb(SAA7134_AUDIO_MUTE_CTRL) & ~(1 << 6));

	atomic_inc(&dev->empress_users);
	file->private_data = dev;
	err = 0;

done:
	mutex_unlock(&dev->empress_tsq.vb_lock);
	return err;
}