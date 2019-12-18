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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int HB_AUDIO_REMAP_MAX_CHANNELS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void remap_s16_interleaved(uint8_t **samples, int nsamples,
                                  int nchannels, int *remap_table)
{
    int ii, jj;
    int16_t *samples_s16 = (int16_t*)(*samples);
    int16_t tmp_buf[HB_AUDIO_REMAP_MAX_CHANNELS];
    for (ii = 0; ii < nsamples; ii++)
    {
        memcpy(tmp_buf, samples_s16, nchannels * sizeof(int16_t));
        for (jj = 0; jj < nchannels; jj++)
        {
            samples_s16[jj] = tmp_buf[remap_table[jj]];
        }
        samples_s16 += nchannels;
    }
}