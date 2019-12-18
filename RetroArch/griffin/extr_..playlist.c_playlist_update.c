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
struct playlist_entry {int /*<<< orphan*/ * crc32; int /*<<< orphan*/ * db_name; int /*<<< orphan*/ * core_name; int /*<<< orphan*/ * core_path; int /*<<< orphan*/ * label; int /*<<< orphan*/ * path; } ;
struct TYPE_3__ {size_t size; int modified; struct playlist_entry* entries; } ;
typedef  TYPE_1__ playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* strdup (int /*<<< orphan*/ *) ; 

void playlist_update(playlist_t *playlist, size_t idx,
      const struct playlist_entry *update_entry)
{
   struct playlist_entry *entry = NULL;

   if (!playlist || idx > playlist->size)
      return;

   entry            = &playlist->entries[idx];

   if (update_entry->path && (update_entry->path != entry->path))
   {
      if (entry->path != NULL)
         free(entry->path);
      entry->path        = strdup(update_entry->path);
      playlist->modified = true;
   }

   if (update_entry->label && (update_entry->label != entry->label))
   {
      if (entry->label != NULL)
         free(entry->label);
      entry->label       = strdup(update_entry->label);
      playlist->modified = true;
   }

   if (update_entry->core_path && (update_entry->core_path != entry->core_path))
   {
      if (entry->core_path != NULL)
         free(entry->core_path);
      entry->core_path   = NULL;
      entry->core_path   = strdup(update_entry->core_path);
      playlist->modified = true;
   }

   if (update_entry->core_name && (update_entry->core_name != entry->core_name))
   {
      if (entry->core_name != NULL)
         free(entry->core_name);
      entry->core_name   = strdup(update_entry->core_name);
      playlist->modified = true;
   }

   if (update_entry->db_name && (update_entry->db_name != entry->db_name))
   {
      if (entry->db_name != NULL)
         free(entry->db_name);
      entry->db_name     = strdup(update_entry->db_name);
      playlist->modified = true;
   }

   if (update_entry->crc32 && (update_entry->crc32 != entry->crc32))
   {
      if (entry->crc32 != NULL)
         free(entry->crc32);
      entry->crc32       = strdup(update_entry->crc32);
      playlist->modified = true;
   }
}