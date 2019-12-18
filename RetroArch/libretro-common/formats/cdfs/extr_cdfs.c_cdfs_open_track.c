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
typedef  int /*<<< orphan*/  intfstream_t ;

/* Variables and functions */
 struct cdfs_track_t* cdfs_open_chd_track (char const*,unsigned int) ; 
 struct cdfs_track_t* cdfs_open_cue_track (char const*,unsigned int) ; 
 char* path_get_extension (char const*) ; 
 scalar_t__ string_is_equal_noncase (char const*,char*) ; 

struct cdfs_track_t* cdfs_open_track(const char* path, unsigned int track_index)
{
   intfstream_t* stream = NULL;
   const char* ext = path_get_extension(path);

   if (string_is_equal_noncase(ext, "cue"))
      return cdfs_open_cue_track(path, track_index);

#ifdef HAVE_CHD
   if (string_is_equal_noncase(ext, "chd"))
      return cdfs_open_chd_track(path, track_index);
#endif

   /* unsupported file type */
   return NULL;
}