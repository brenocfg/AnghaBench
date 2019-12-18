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
struct playlist_entry {size_t size; struct playlist_entry* entries; struct playlist_entry* default_core_name; struct playlist_entry* default_core_path; struct playlist_entry* conf_path; } ;
typedef  struct playlist_entry playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct playlist_entry*) ; 
 int /*<<< orphan*/  playlist_free_entry (struct playlist_entry*) ; 

void playlist_free(playlist_t *playlist)
{
   size_t i;

   if (!playlist)
      return;

   if (playlist->conf_path != NULL)
      free(playlist->conf_path);
   playlist->conf_path = NULL;

   if (playlist->default_core_path != NULL)
      free(playlist->default_core_path);
   playlist->default_core_path = NULL;

   if (playlist->default_core_name != NULL)
      free(playlist->default_core_name);
   playlist->default_core_name = NULL;

   for (i = 0; i < playlist->size; i++)
   {
      struct playlist_entry *entry = &playlist->entries[i];

      if (entry)
         playlist_free_entry(entry);
   }

   free(playlist->entries);
   playlist->entries = NULL;

   free(playlist);
}