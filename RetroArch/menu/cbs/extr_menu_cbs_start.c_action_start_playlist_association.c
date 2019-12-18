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
typedef  int /*<<< orphan*/  playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_DETECT ; 
 int /*<<< orphan*/  file_path_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_set_default_core_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_set_default_core_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int action_start_playlist_association(unsigned type, const char *label)
{
   playlist_t *playlist  = playlist_get_cached();

   if (!playlist)
      return -1;

   /* Set default core path + name to DETECT */
   playlist_set_default_core_path(playlist, file_path_str(FILE_PATH_DETECT));
   playlist_set_default_core_name(playlist, file_path_str(FILE_PATH_DETECT));
   playlist_write_file(playlist);

   return 0;
}