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
struct resampler_data {float const* data_in; float* data_out; size_t input_frames; float ratio; scalar_t__ output_frames; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (void*) ;int /*<<< orphan*/  (* process ) (void*,struct resampler_data*) ;} ;
typedef  TYPE_1__ retro_resampler_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESAMPLER_QUALITY_DONTCARE ; 
 scalar_t__ memalign_alloc (int,size_t) ; 
 int /*<<< orphan*/  retro_resampler_realloc (void**,TYPE_1__ const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float) ; 
 scalar_t__ s_rate ; 
 int /*<<< orphan*/  stub1 (void*,struct resampler_data*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

__attribute__((used)) static bool one_shot_resample(const float* in, size_t samples_in,
      unsigned rate, float** out, size_t* samples_out)
{
   struct resampler_data info;
   void* data                         = NULL;
   const retro_resampler_t* resampler = NULL;
   float ratio                        = (double)s_rate / (double)rate;

   if (!retro_resampler_realloc(&data, &resampler, NULL,
            RESAMPLER_QUALITY_DONTCARE, ratio))
      return false;

   /*
    * Allocate on a 16-byte boundary, and pad to a multiple of 16 bytes. We
    * add four more samples in the formula below just as safeguard, because
    * resampler->process sometimes reports more output samples than the
    * formula below calculates. Ideally, audio resamplers should have a
    * function to return the number of samples they will output given a
    * count of input samples.
    */
   *samples_out                       = samples_in * ratio + 4;
   *out                               = (float*)memalign_alloc(16,
         ((*samples_out + 15) & ~15) * sizeof(float));

   if (*out == NULL)
      return false;

   info.data_in                       = in;
   info.data_out                      = *out;
   info.input_frames                  = samples_in / 2;
   info.output_frames                 = 0;
   info.ratio                         = ratio;

   resampler->process(data, &info);
   resampler->free(data);
   return true;
}