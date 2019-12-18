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
struct playlist_entry {int dummy; } ;
struct TYPE_3__ {size_t size; int modified; scalar_t__ entries; } ;
typedef  TYPE_1__ playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  playlist_free_entry (struct playlist_entry*) ; 

void playlist_delete_index(playlist_t *playlist,
      size_t idx)
{
   struct playlist_entry *entry_to_delete = NULL;

   if (!playlist)
      return;

   if (idx >= playlist->size)
      return;

   playlist->size     = playlist->size - 1;

   /* Free unwanted entry */
   entry_to_delete = (struct playlist_entry *)(playlist->entries + idx);
   if (entry_to_delete)
      playlist_free_entry(entry_to_delete);

   /* Shift remaining entries to fill the gap */
   memmove(playlist->entries + idx, playlist->entries + idx + 1,
         (playlist->size - idx) * sizeof(struct playlist_entry));

   playlist->modified = true;
}