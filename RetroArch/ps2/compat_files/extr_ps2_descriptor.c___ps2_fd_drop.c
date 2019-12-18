#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ref_count; int current_folder_position; int /*<<< orphan*/  FileEntry; } ;
typedef  TYPE_1__ DescriptorTranslation ;

/* Variables and functions */
 int /*<<< orphan*/  _lock () ; 
 int /*<<< orphan*/  _unlock () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __ps2_fd_drop(DescriptorTranslation *map)
{
   _lock();

   if (map->ref_count == 1)
   {
      map->ref_count--;
      map->current_folder_position = -1;
      free(map->FileEntry);
      memset(map, 0, sizeof(DescriptorTranslation));
   }
   else
   {
      map->ref_count--;
   }

   _unlock();
   return 0;
}