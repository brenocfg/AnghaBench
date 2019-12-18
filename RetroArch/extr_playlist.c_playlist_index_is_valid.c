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
struct TYPE_5__ {size_t size; TYPE_1__* entries; } ;
typedef  TYPE_2__ playlist_t ;
struct TYPE_4__ {char const* path; char const* core_path; } ;

/* Variables and functions */
 char const* path_basename (char const*) ; 
 scalar_t__ string_is_equal (char const*,char const*) ; 

bool playlist_index_is_valid(playlist_t *playlist, size_t idx,
      const char *path, const char *core_path)
{
   if (!playlist)
      return false;

   if (idx >= playlist->size)
      return false;

   return string_is_equal(playlist->entries[idx].path, path) &&
          string_is_equal(path_basename(playlist->entries[idx].core_path), path_basename(core_path));
}