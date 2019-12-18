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
struct TYPE_3__ {size_t size; struct playlist_entry* entries; } ;
typedef  TYPE_1__ playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  playlist_free_entry (struct playlist_entry*) ; 

void playlist_clear(playlist_t *playlist)
{
   size_t i;
   if (!playlist)
      return;

   for (i = 0; i < playlist->size; i++)
   {
      struct playlist_entry *entry = &playlist->entries[i];

      if (entry)
         playlist_free_entry(entry);
   }
   playlist->size = 0;
}