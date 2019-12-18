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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 int const AV_SAMPLE_FMT_NONE ; 

__attribute__((used)) static bool ffmpeg_codec_has_sample_format(enum AVSampleFormat fmt,
      const enum AVSampleFormat *fmts)
{
   unsigned i;

   for (i = 0; fmts[i] != AV_SAMPLE_FMT_NONE; i++)
      if (fmt == fmts[i])
         return true;
   return false;
}