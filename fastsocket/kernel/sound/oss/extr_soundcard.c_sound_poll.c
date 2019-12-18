#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 unsigned int DMAbuf_poll (struct file*,int,int /*<<< orphan*/ *) ; 
 unsigned int MIDIbuf_poll (int,struct file*,int /*<<< orphan*/ *) ; 
#define  SND_DEV_AUDIO 133 
#define  SND_DEV_DSP 132 
#define  SND_DEV_DSP16 131 
#define  SND_DEV_MIDIN 130 
#define  SND_DEV_SEQ 129 
#define  SND_DEV_SEQ2 128 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 unsigned int sequencer_poll (int,struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int sound_poll(struct file *file, poll_table * wait)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	int dev = iminor(inode);

	DEB(printk("sound_poll(dev=%d)\n", dev));
	switch (dev & 0x0f) {
	case SND_DEV_SEQ:
	case SND_DEV_SEQ2:
		return sequencer_poll(dev, file, wait);

	case SND_DEV_MIDIN:
		return MIDIbuf_poll(dev, file, wait);

	case SND_DEV_DSP:
	case SND_DEV_DSP16:
	case SND_DEV_AUDIO:
		return DMAbuf_poll(file, dev >> 4, wait);
	}
	return 0;
}