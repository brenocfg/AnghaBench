#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ resampler_data; TYPE_1__* resampler; scalar_t__ resample_buf; scalar_t__ float_resample_buf; scalar_t__ float_buf; scalar_t__ upsample_buf; struct TYPE_7__* buf; struct TYPE_7__* rwav; scalar_t__ samples; } ;
typedef  TYPE_2__ audio_chunk_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memalign_free (scalar_t__) ; 
 int /*<<< orphan*/  rwav_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void audio_mix_free_chunk(audio_chunk_t *chunk)
{
   if (!chunk)
      return;

   if (chunk->rwav && chunk->rwav->samples)
   {
      /* rwav_free only frees the samples */
      rwav_free(chunk->rwav);
      free(chunk->rwav);
   }

   if (chunk->buf)
      free(chunk->buf);

   if (chunk->upsample_buf)
      memalign_free(chunk->upsample_buf);

   if (chunk->float_buf)
      memalign_free(chunk->float_buf);

   if (chunk->float_resample_buf)
      memalign_free(chunk->float_resample_buf);

   if (chunk->resample_buf)
      memalign_free(chunk->resample_buf);

   if (chunk->resampler && chunk->resampler_data)
      chunk->resampler->free(chunk->resampler_data);

   free(chunk);
}