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
struct cdfs_track_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHDSTREAM_TRACK_PRIMARY ; 
 struct cdfs_track_t* cdfs_open_chd_track (char const*,int /*<<< orphan*/ ) ; 
 struct cdfs_track_t* cdfs_open_cue_track (char const*,int /*<<< orphan*/ ) ; 
 struct cdfs_track_t* cdfs_open_raw_track (char const*) ; 
 char* path_get_extension (char const*) ; 
 scalar_t__ string_is_equal_noncase (char const*,char*) ; 

struct cdfs_track_t* cdfs_open_data_track(const char* path)
{
   const char* ext = path_get_extension(path);

   if (string_is_equal_noncase(ext, "cue"))
      return cdfs_open_cue_track(path, 0);

#ifdef HAVE_CHD
   if (string_is_equal_noncase(ext, "chd"))
      return cdfs_open_chd_track(path, CHDSTREAM_TRACK_PRIMARY);
#endif

   /* unsupported file type - try opening as a raw track */
   return cdfs_open_raw_track(path);
}