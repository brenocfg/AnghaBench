#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_2__ {scalar_t__ encoding; int samplefmt; unsigned int sample_size; } ;

/* Variables and functions */
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 TYPE_1__* samplefmt_to_encoding_table ; 

__attribute__((used)) static unsigned int samplefmt_to_sample_size(enum AVSampleFormat samplefmt)
{
   unsigned int i;
   for(i = 0; samplefmt_to_encoding_table[i].encoding != MMAL_ENCODING_UNKNOWN; i++)
      if(samplefmt_to_encoding_table[i].samplefmt == samplefmt) break;
   return samplefmt_to_encoding_table[i].sample_size;
}