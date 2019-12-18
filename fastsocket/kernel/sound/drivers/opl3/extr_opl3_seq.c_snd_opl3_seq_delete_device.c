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
struct snd_seq_device {int dummy; } ;
struct snd_opl3 {int seq_client; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_SEQ_DEVICE_ARGPTR (struct snd_seq_device*) ; 
 int /*<<< orphan*/  snd_opl3_free_seq_oss (struct snd_opl3*) ; 
 int /*<<< orphan*/  snd_seq_delete_kernel_client (int) ; 

__attribute__((used)) static int snd_opl3_seq_delete_device(struct snd_seq_device *dev)
{
	struct snd_opl3 *opl3;

	opl3 = *(struct snd_opl3 **)SNDRV_SEQ_DEVICE_ARGPTR(dev);
	if (opl3 == NULL)
		return -EINVAL;

#ifdef CONFIG_SND_SEQUENCER_OSS
	snd_opl3_free_seq_oss(opl3);
#endif
	if (opl3->seq_client >= 0) {
		snd_seq_delete_kernel_client(opl3->seq_client);
		opl3->seq_client = -1;
	}
	return 0;
}