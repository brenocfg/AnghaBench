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
struct file {struct audio_in* private_data; } ;
struct audio_in {int agc; int ns; int iir; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  enable_mask ;

/* Variables and functions */
 int AGC_ENABLE ; 
 int AGC_PARAM_SIZE ; 
#define  AUDIO_ENABLE_AUDPRE 131 
#define  AUDIO_SET_AGC 130 
#define  AUDIO_SET_NS 129 
#define  AUDIO_SET_TX_IIR 128 
 int EFAULT ; 
 int EINVAL ; 
 int IIR_ENABLE ; 
 int IIR_PARAM_SIZE ; 
 int NS_ENABLE ; 
 int NS_PARAM_SIZE ; 
 int /*<<< orphan*/  audio_enable_agc (struct audio_in*,int) ; 
 int /*<<< orphan*/  audio_enable_ns (struct audio_in*,int) ; 
 int /*<<< orphan*/  audio_enable_tx_iir (struct audio_in*,int) ; 
 int /*<<< orphan*/  copy_from_user (int*,void*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static long audpre_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct audio_in *audio = file->private_data;
	int rc = 0, enable;
	uint16_t enable_mask;
#if DEBUG
	int i;
#endif

	mutex_lock(&audio->lock);
	switch (cmd) {
	case AUDIO_ENABLE_AUDPRE: {
		if (copy_from_user(&enable_mask, (void *) arg,
				sizeof(enable_mask)))
			goto out_fault;

		enable = (enable_mask & AGC_ENABLE) ? 1 : 0;
		audio_enable_agc(audio, enable);
		enable = (enable_mask & NS_ENABLE) ? 1 : 0;
		audio_enable_ns(audio, enable);
		enable = (enable_mask & IIR_ENABLE) ? 1 : 0;
		audio_enable_tx_iir(audio, enable);
		break;
	}
	case AUDIO_SET_AGC: {
		if (copy_from_user(&audio->agc, (void *) arg,
				sizeof(audio->agc)))
			goto out_fault;
#if DEBUG
		pr_info("set agc\n");
		for (i = 0; i < AGC_PARAM_SIZE; i++) \
			pr_info("agc_params[%d] = 0x%04x\n", i,
				audio->agc.agc_params[i]);
#endif
		break;
	}
	case AUDIO_SET_NS: {
		if (copy_from_user(&audio->ns, (void *) arg,
				sizeof(audio->ns)))
			goto out_fault;
#if DEBUG
		pr_info("set ns\n");
		for (i = 0; i < NS_PARAM_SIZE; i++) \
			pr_info("ns_params[%d] = 0x%04x\n",
				i, audio->ns.ns_params[i]);
#endif
		break;
	}
	case AUDIO_SET_TX_IIR: {
		if (copy_from_user(&audio->iir, (void *) arg,
				sizeof(audio->iir)))
			goto out_fault;
#if DEBUG
		pr_info("set iir\n");
		pr_info("iir.num_bands = 0x%04x\n", audio->iir.num_bands);
		for (i = 0; i < IIR_PARAM_SIZE; i++) \
			pr_info("iir_params[%d] = 0x%04x\n",
				i, audio->iir.iir_params[i]);
#endif
		break;
	}
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