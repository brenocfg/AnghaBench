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
typedef  int /*<<< orphan*/  real_core_path ;
struct TYPE_3__ {char* default_core_path; int modified; } ;
typedef  TYPE_1__ playlist_t ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  PLAYLIST_SAVE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  playlist_resolve_path (int /*<<< orphan*/ ,char*,int) ; 
 char* strdup (char*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

void playlist_set_default_core_path(playlist_t *playlist, const char *core_path)
{
   char real_core_path[PATH_MAX_LENGTH];

   real_core_path[0] = '\0';

   if (!playlist || string_is_empty(core_path))
      return;

   /* Get 'real' core path */
   strlcpy(real_core_path, core_path, sizeof(real_core_path));
   if (!string_is_equal(real_core_path, "DETECT"))
       playlist_resolve_path(PLAYLIST_SAVE, real_core_path, sizeof(real_core_path));

   if (string_is_empty(real_core_path))
      return;

   if (!string_is_equal(playlist->default_core_path, real_core_path))
   {
      if (playlist->default_core_path)
         free(playlist->default_core_path);
      playlist->default_core_path = strdup(real_core_path);
      playlist->modified = true;
   }
}