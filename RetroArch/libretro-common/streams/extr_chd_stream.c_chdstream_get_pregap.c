#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ pregap; scalar_t__ frames; scalar_t__ extra; } ;
typedef  TYPE_1__ metadata_t ;
struct TYPE_6__ {scalar_t__ track_frame; int /*<<< orphan*/  chd; } ;
typedef  TYPE_2__ chdstream_t ;

/* Variables and functions */
 scalar_t__ chdstream_get_meta (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 

uint32_t chdstream_get_pregap(chdstream_t *stream)
{
   metadata_t meta;
   uint32_t frame_offset = 0;
   uint32_t i;

   for (i = 0; chdstream_get_meta(stream->chd, i, &meta); ++i)
   {
      if (stream->track_frame == frame_offset)
         return meta.pregap;

      frame_offset += meta.frames + meta.extra;
   }

   return 0;
}