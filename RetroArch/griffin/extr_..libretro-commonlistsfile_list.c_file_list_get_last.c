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
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_1__ file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_get_at_offset (TYPE_1__ const*,scalar_t__,char const**,char const**,unsigned int*,size_t*) ; 

void file_list_get_last(const file_list_t *list,
      const char **path, const char **label,
      unsigned *file_type, size_t *entry_idx)
{
   if (list && list->size)
      file_list_get_at_offset(list, list->size - 1, path, label, file_type, entry_idx);
}