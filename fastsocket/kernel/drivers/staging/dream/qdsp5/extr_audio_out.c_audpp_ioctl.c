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
typedef  int uint16_t ;
struct file {struct audio* private_data; } ;
struct audio {int adrc; int eq; int iir; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  enable_mask ;

/* Variables and functions */
 int ADRC_ENABLE ; 
#define  AUDIO_ENABLE_AUDPP 131 
#define  AUDIO_SET_ADRC 130 
#define  AUDIO_SET_EQ 129 
#define  AUDIO_SET_RX_IIR 128 
 int EFAULT ; 
 int EINVAL ; 
 int EQ_ENABLE ; 
 int IIR_ENABLE ; 
 int /*<<< orphan*/  audio_enable_adrc (struct audio*,int) ; 
 int /*<<< orphan*/  audio_enable_eq (struct audio*,int) ; 
 int /*<<< orphan*/  audio_enable_rx_iir (struct audio*,int) ; 
 int /*<<< orphan*/  copy_from_user (int*,void*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long audpp_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct audio *audio = file->private_data;
	int rc = 0, enable;
	uint16_t enable_mask;

	mutex_lock(&audio->lock);
	switch (cmd) {
	case AUDIO_ENABLE_AUDPP:
		if (copy_from_user(&enable_mask, (void *) arg, sizeof(enable_mask)))
			goto out_fault;

		enable = (enable_mask & ADRC_ENABLE)? 1 : 0;
		audio_enable_adrc(audio, enable);
		enable = (enable_mask & EQ_ENABLE)? 1 : 0;
		audio_enable_eq(audio, enable);
		enable = (enable_mask & IIR_ENABLE)? 1 : 0;
		audio_enable_rx_iir(audio, enable);
		break;

	case AUDIO_SET_ADRC:
		if (copy_from_user(&audio->adrc, (void*) arg, sizeof(audio->adrc)))
			goto out_fault;
		break;

	case AUDIO_SET_EQ:
		if (copy_from_user(&audio->eq, (void*) arg, sizeof(audio->eq)))
			goto out_fault;
		break;

	case AUDIO_SET_RX_IIR:
		if (copy_from_user(&audio->iir, (void*) arg, sizeof(audio->iir)))
			goto out_fault;
		break;

	default:
		rc = -EINVAL;
	}

	goto out;

 out_fault:
	rc = -EFAULT;
 out:
	mutex_unlock(&audio->lock);
	return rc;
}