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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_PCM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_PCM_PLAYBACK ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 scalar_t__ imajor (struct inode*) ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  snd_lookup_minor_data (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_major ; 

__attribute__((used)) static struct file *snd_pcm_file_fd(int fd)
{
	struct file *file;
	struct inode *inode;
	unsigned int minor;

	file = fget(fd);
	if (!file)
		return NULL;
	inode = file->f_path.dentry->d_inode;
	if (!S_ISCHR(inode->i_mode) ||
	    imajor(inode) != snd_major) {
		fput(file);
		return NULL;
	}
	minor = iminor(inode);
	if (!snd_lookup_minor_data(minor, SNDRV_DEVICE_TYPE_PCM_PLAYBACK) &&
	    !snd_lookup_minor_data(minor, SNDRV_DEVICE_TYPE_PCM_CAPTURE)) {
		fput(file);
		return NULL;
	}
	return file;
}