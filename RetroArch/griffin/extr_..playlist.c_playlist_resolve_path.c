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
typedef  int /*<<< orphan*/  tmp ;
typedef  enum playlist_file_mode { ____Placeholder_playlist_file_mode } playlist_file_mode ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int PLAYLIST_LOAD ; 
 int /*<<< orphan*/  fill_pathname_abbreviate_special (char*,char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_expand_special (char*,char*,int) ; 
 int /*<<< orphan*/  path_resolve_realpath (char*,size_t,int) ; 
 int /*<<< orphan*/  realpath (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

void playlist_resolve_path(enum playlist_file_mode mode,
      char *path, size_t size)
{
#ifdef HAVE_COCOATOUCH
   char tmp[PATH_MAX_LENGTH];

   if (mode == PLAYLIST_LOAD)
   {
      fill_pathname_expand_special(tmp, path, sizeof(tmp));
      strlcpy(path, tmp, size);
   }
   else
   {
      /* iOS needs to call realpath here since the call
       * above fails due to possibly buffer related issues.
       * Try to expand the path to ensure that it gets saved
       * correctly. The path can be abbreviated if saving to
       * a playlist from another playlist (ex: content history to favorites)
       */
      char tmp2[PATH_MAX_LENGTH];
      fill_pathname_expand_special(tmp, path, sizeof(tmp));
      realpath(tmp, tmp2);
      fill_pathname_abbreviate_special(path, tmp2, size);
   }
#else
   if (mode == PLAYLIST_LOAD)
      return;

   path_resolve_realpath(path, size, true);
#endif
}