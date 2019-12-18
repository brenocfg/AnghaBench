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
struct playlist_entry {int dummy; } ;
typedef  int /*<<< orphan*/  playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_update (int /*<<< orphan*/ *,size_t,struct playlist_entry const*) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 

void command_playlist_update_write(
      playlist_t *plist,
      size_t idx,
      const struct playlist_entry *entry)
{
   playlist_t *playlist = plist ? plist : playlist_get_cached();

   if (!playlist)
      return;

   playlist_update(
         playlist,
         idx,
         entry);

   playlist_write_file(playlist);
}