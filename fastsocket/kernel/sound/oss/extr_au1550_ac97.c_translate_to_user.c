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
struct dmabuf {int num_channels; int sample_size; int src_factor; int dma_bytes_per_sample; int user_bytes_per_sample; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int EFAULT ; 
 char S16_TO_U8 (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_to_user (char*,char*,int) ; 

__attribute__((used)) static int
translate_to_user(struct dmabuf *db, char* userbuf, char* dmabuf,
							     int dmacount)
{
	int             sample, i;
	int             interp_bytes_per_sample;
	int             num_samples;
	int             mono = (db->num_channels == 1);
	char            usersample[12];

	if (db->sample_size == 16 && !mono && db->src_factor == 1) {
		/* no translation necessary, just copy
		*/
		if (copy_to_user(userbuf, dmabuf, dmacount))
			return -EFAULT;
		return dmacount;
	}

	interp_bytes_per_sample = db->dma_bytes_per_sample * db->src_factor;
	num_samples = dmacount / interp_bytes_per_sample;

	for (sample = 0; sample < num_samples; sample++) {
		for (i = 0; i < db->num_channels; i++) {
			if (db->sample_size == 8)
				usersample[i] =
					S16_TO_U8(*((s16 *) (&dmabuf[i * 2])));
			else
				*((s16 *) (&usersample[i * 2])) =
					*((s16 *) (&dmabuf[i * 2]));
		}

		if (copy_to_user(userbuf, usersample,
				 db->user_bytes_per_sample)) {
			return -EFAULT;
		}

		userbuf += db->user_bytes_per_sample;
		dmabuf += interp_bytes_per_sample;
	}

	return num_samples * interp_bytes_per_sample;
}