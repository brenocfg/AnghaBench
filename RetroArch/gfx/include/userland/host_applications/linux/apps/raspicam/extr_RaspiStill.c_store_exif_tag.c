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
struct TYPE_3__ {size_t numExifTags; char const** exifTags; } ;
typedef  TYPE_1__ RASPISTILL_STATE ;

/* Variables and functions */
 size_t MAX_USER_EXIF_TAGS ; 

__attribute__((used)) static void store_exif_tag(RASPISTILL_STATE *state, const char *exif_tag)
{
   if (state->numExifTags < MAX_USER_EXIF_TAGS)
   {
      state->exifTags[state->numExifTags] = exif_tag;
      state->numExifTags++;
   }
}