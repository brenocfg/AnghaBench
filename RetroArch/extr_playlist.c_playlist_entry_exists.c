#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  real_search_path ;
struct TYPE_5__ {size_t size; TYPE_1__* entries; } ;
typedef  TYPE_2__ playlist_t ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  path_resolve_realpath (char*,int,int) ; 
 scalar_t__ playlist_path_equal (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

bool playlist_entry_exists(playlist_t *playlist,
      const char *path,
      const char *crc32)
{
   size_t i;
   char real_search_path[PATH_MAX_LENGTH];

   real_search_path[0] = '\0';

   if (!playlist || string_is_empty(path))
      return false;

   /* Get 'real' search path */
   strlcpy(real_search_path, path, sizeof(real_search_path));
   path_resolve_realpath(real_search_path, sizeof(real_search_path), true);

   for (i = 0; i < playlist->size; i++)
      if (playlist_path_equal(real_search_path, playlist->entries[i].path))
         return true;

   return false;
}