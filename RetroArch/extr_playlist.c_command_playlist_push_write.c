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
 scalar_t__ playlist_push (int /*<<< orphan*/ *,struct playlist_entry const*) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 

void command_playlist_push_write(
      playlist_t *playlist,
      const struct playlist_entry *entry)
{
   if (!playlist)
      return;

   if (playlist_push(
         playlist,
         entry
         ))
      playlist_write_file(playlist);
}