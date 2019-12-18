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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNDRV_MINOR_OSS_MUSIC ; 
 int SNDRV_SEQ_OSS_MODE_MUSIC ; 
 int SNDRV_SEQ_OSS_MODE_SYNTH ; 
 scalar_t__ iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 int snd_seq_oss_open (struct file*,int) ; 

__attribute__((used)) static int
odev_open(struct inode *inode, struct file *file)
{
	int level, rc;

	if (iminor(inode) == SNDRV_MINOR_OSS_MUSIC)
		level = SNDRV_SEQ_OSS_MODE_MUSIC;
	else
		level = SNDRV_SEQ_OSS_MODE_SYNTH;

	mutex_lock(&register_mutex);
	rc = snd_seq_oss_open(file, level);
	mutex_unlock(&register_mutex);

	return rc;
}