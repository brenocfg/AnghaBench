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
struct saa7134_dev {int /*<<< orphan*/  empress_users; int /*<<< orphan*/  empress_tsq; } ;
struct file {struct saa7134_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_AUDIO_MUTE_CTRL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_reset_encoder (struct saa7134_dev*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ts_release(struct file *file)
{
	struct saa7134_dev *dev = file->private_data;

	videobuf_stop(&dev->empress_tsq);
	videobuf_mmap_free(&dev->empress_tsq);

	/* stop the encoder */
	ts_reset_encoder(dev);

	/* Mute audio */
	saa_writeb(SAA7134_AUDIO_MUTE_CTRL,
		saa_readb(SAA7134_AUDIO_MUTE_CTRL) | (1 << 6));

	atomic_dec(&dev->empress_users);

	return 0;
}