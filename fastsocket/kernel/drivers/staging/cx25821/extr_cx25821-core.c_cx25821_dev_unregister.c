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
struct cx25821_dev {int /*<<< orphan*/ * i2c_bus; int /*<<< orphan*/  refcount; int /*<<< orphan*/  pci; int /*<<< orphan*/  base_io_addr; } ;

/* Variables and functions */
 int AUDIO_UPSTREAM_SRAM_CHANNEL_B ; 
 int VID_CHANNEL_NUM ; 
 int VID_UPSTREAM_SRAM_CHANNEL_I ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx25821_free_mem_upstream_audio (struct cx25821_dev*) ; 
 int /*<<< orphan*/  cx25821_free_mem_upstream_ch1 (struct cx25821_dev*) ; 
 int /*<<< orphan*/  cx25821_free_mem_upstream_ch2 (struct cx25821_dev*) ; 
 int /*<<< orphan*/  cx25821_i2c_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx25821_iounmap (struct cx25821_dev*) ; 
 int /*<<< orphan*/  cx25821_video_unregister (struct cx25821_dev*,int) ; 
 int /*<<< orphan*/  cx25821_videoioctl_unregister (struct cx25821_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx25821_dev_unregister(struct cx25821_dev *dev)
{
	int i;

	if (!dev->base_io_addr)
		return;

	cx25821_free_mem_upstream_ch1(dev);
	cx25821_free_mem_upstream_ch2(dev);
	cx25821_free_mem_upstream_audio(dev);

	release_mem_region(dev->base_io_addr, pci_resource_len(dev->pci, 0));

	if (!atomic_dec_and_test(&dev->refcount))
		return;

	for (i = 0; i < VID_CHANNEL_NUM; i++)
		cx25821_video_unregister(dev, i);

	for (i = VID_UPSTREAM_SRAM_CHANNEL_I;
	     i <= AUDIO_UPSTREAM_SRAM_CHANNEL_B; i++) {
		cx25821_video_unregister(dev, i);
	}

	cx25821_videoioctl_unregister(dev);

	cx25821_i2c_unregister(&dev->i2c_bus[0]);
	cx25821_iounmap(dev);
}