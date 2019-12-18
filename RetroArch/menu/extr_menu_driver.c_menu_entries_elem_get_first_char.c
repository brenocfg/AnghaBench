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
struct TYPE_4__ {char* alt; char* path; } ;

/* Variables and functions */
 int tolower (int) ; 

__attribute__((used)) static int menu_entries_elem_get_first_char(
      file_list_t *list, unsigned offset)
{
   int ret          = 0;
   const char *path = NULL;

   if (list)
      if ((path = list->list[offset].alt
         ? list->list[offset].alt 
         : list->list[offset].path))
         ret = tolower((int)*path);

   /* "Normalize" non-alphabetical entries so they
    * are lumped together for purposes of jumping. */
   if (ret < 'a')
      return ('a' - 1);
   else if (ret > 'z')
      return ('z' + 1);
   return ret;
}