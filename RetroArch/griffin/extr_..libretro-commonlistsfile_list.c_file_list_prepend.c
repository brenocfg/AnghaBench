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
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int file_list_insert (int /*<<< orphan*/ *,char const*,char const*,unsigned int,size_t,size_t,int /*<<< orphan*/ ) ; 

bool file_list_prepend(file_list_t *list,
      const char *path, const char *label,
      unsigned type, size_t directory_ptr,
      size_t entry_idx)
{
   return file_list_insert(list, path,
      label, type,
      directory_ptr, entry_idx,
      0
   );
}