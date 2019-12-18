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
struct v4l2_frequency {int /*<<< orphan*/  frequency; } ;
struct gemtek_pci {int mute; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GEMTEK_PCI_RANGE_HIGH ; 
 int /*<<< orphan*/  GEMTEK_PCI_RANGE_LOW ; 
 int /*<<< orphan*/  gemtek_pci_setfrequency (struct gemtek_pci*,int /*<<< orphan*/ ) ; 
 struct gemtek_pci* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
					struct v4l2_frequency *f)
{
	struct gemtek_pci *card = video_drvdata(file);

	if (f->frequency < GEMTEK_PCI_RANGE_LOW ||
	    f->frequency > GEMTEK_PCI_RANGE_HIGH)
		return -EINVAL;
	gemtek_pci_setfrequency(card, f->frequency);
	card->mute = false;
	return 0;
}