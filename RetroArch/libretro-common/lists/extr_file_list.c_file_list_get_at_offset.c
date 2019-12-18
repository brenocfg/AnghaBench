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
struct TYPE_5__ {TYPE_1__* list; } ;
typedef  TYPE_2__ file_list_t ;
struct TYPE_4__ {char* path; char* label; unsigned int type; size_t entry_idx; } ;

/* Variables and functions */

void file_list_get_at_offset(const file_list_t *list, size_t idx,
      const char **path, const char **label, unsigned *file_type,
      size_t *entry_idx)
{
   if (!list)
      return;

   if (path)
      *path      = list->list[idx].path;
   if (label)
      *label     = list->list[idx].label;
   if (file_type)
      *file_type = list->list[idx].type;
   if (entry_idx)
      *entry_idx = list->list[idx].entry_idx;
}