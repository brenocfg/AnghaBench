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
struct TYPE_2__ {scalar_t__ encoding; scalar_t__ pixel_format; } ;
typedef  scalar_t__ MMAL_FOURCC_T ;
typedef  scalar_t__ BRCMJPEG_PIXEL_FORMAT_T ;

/* Variables and functions */
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 TYPE_1__* mmal_raw_conversion ; 

__attribute__((used)) static MMAL_FOURCC_T brcmjpeg_pixfmt_to_encoding(BRCMJPEG_PIXEL_FORMAT_T pixel_format)
{
   unsigned int i;
   for (i = 0; mmal_raw_conversion[i].encoding != MMAL_ENCODING_UNKNOWN; i++)
      if (mmal_raw_conversion[i].pixel_format == pixel_format)
         break;
   return mmal_raw_conversion[i].encoding;
}