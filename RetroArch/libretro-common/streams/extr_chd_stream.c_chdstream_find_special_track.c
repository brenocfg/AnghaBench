#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int track; int /*<<< orphan*/  frames; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ metadata_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  chd_file ;

/* Variables and functions */
#define  CHDSTREAM_TRACK_FIRST_DATA 129 
 int CHDSTREAM_TRACK_LAST ; 
#define  CHDSTREAM_TRACK_PRIMARY 128 
 int chdstream_find_track_number (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
chdstream_find_special_track(chd_file *fd, int32_t track, metadata_t *meta)
{
   int32_t i;
   metadata_t iter;
   int32_t largest_track = 0;
   uint32_t largest_size = 0;

   for (i = 1; true; ++i)
   {
      if (!chdstream_find_track_number(fd, i, &iter))
      {
         if (track == CHDSTREAM_TRACK_LAST && i > 1)
         {
            *meta = iter;
            return true;
         }
         else if (track == CHDSTREAM_TRACK_PRIMARY && largest_track != 0)
            return chdstream_find_track_number(fd, largest_track, meta);
      }

      switch (track)
      {
         case CHDSTREAM_TRACK_FIRST_DATA:
            if (strcmp(iter.type, "AUDIO"))
            {
               *meta = iter;
               return true;
            }
            break;
         case CHDSTREAM_TRACK_PRIMARY:
            if (strcmp(iter.type, "AUDIO") && iter.frames > largest_size)
            {
               largest_size = iter.frames;
               largest_track = iter.track;
            }
            break;
         default:
            break;
      }
   }
}