#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {TYPE_1__* rwav; scalar_t__ upsample_buf; scalar_t__ resample_buf; scalar_t__ resample; } ;
typedef  TYPE_2__ audio_chunk_t ;
struct TYPE_4__ {int bitspersample; int numchannels; } ;

/* Variables and functions */

int16_t audio_mix_get_chunk_sample(audio_chunk_t *chunk, unsigned channel, size_t index)
{
   if (!chunk)
      return 0;

   if (chunk->rwav)
   {
      int sample_size    = chunk->rwav->bitspersample / 8;
      int16_t sample_out = 0;

      /* 0 is the first/left channel */
      uint8_t *sample    = NULL;

      if (chunk->resample)
         sample = (uint8_t*)chunk->resample_buf +
            (sample_size * index * chunk->rwav->numchannels) + (channel * sample_size);
      else
         sample = (uint8_t*)chunk->upsample_buf +
            (sample_size * index * chunk->rwav->numchannels) + (channel * sample_size);

      sample_out = (int16_t)*sample;

      return sample_out;
   }

   /* no other filetypes supported yet */
   return 0;
}