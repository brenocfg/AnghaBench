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
typedef  scalar_t__ int64_t ;
typedef  int VC_CONTAINER_SEEK_FLAGS_T ;

/* Variables and functions */
 int VC_CONTAINER_SEEK_FLAG_FORWARD ; 

__attribute__((used)) static int avi_compare_seek_time(int64_t chunk_time, int64_t seek_time,
   int chunk_is_keyframe, VC_CONTAINER_SEEK_FLAGS_T seek_flags)
{
   if (chunk_time == seek_time && chunk_is_keyframe && !(seek_flags & VC_CONTAINER_SEEK_FLAG_FORWARD))
      return 0;

   if (chunk_time > seek_time && chunk_is_keyframe && (seek_flags & VC_CONTAINER_SEEK_FLAG_FORWARD))
      return 0;

   if (chunk_time > seek_time && !(seek_flags & VC_CONTAINER_SEEK_FLAG_FORWARD))
      return 1; /* Chunk time is past seek time, caller should use the previous keyframe */

   return -1;
}