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
struct TYPE_5__ {size_t resample_len; TYPE_1__* rwav; scalar_t__ resample; } ;
typedef  TYPE_2__ audio_chunk_t ;
struct TYPE_4__ {size_t numsamples; } ;

/* Variables and functions */

size_t audio_mix_get_chunk_num_samples(audio_chunk_t *chunk)
{
   if (!chunk)
      return 0;

   if (chunk->rwav)
   {
      if (chunk->resample)
         return chunk->resample_len;
      return chunk->rwav->numsamples;
   }

   /* no other filetypes supported yet */
   return 0;
}