#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int /*<<< orphan*/ * upsample_buf; int /*<<< orphan*/ * resample_buf; scalar_t__ resample; scalar_t__ rwav; } ;
typedef  TYPE_1__ audio_chunk_t ;

/* Variables and functions */

int16_t* audio_mix_get_chunk_samples(audio_chunk_t *chunk)
{
   if (!chunk)
      return 0;

   if (chunk->rwav)
   {
      int16_t *sample;

      if (chunk->resample)
         sample = chunk->resample_buf;
      else
         sample = chunk->upsample_buf;

      return sample;
   }

   return NULL;
}