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
struct string_list_elem {int dummy; } ;
struct string_list {int /*<<< orphan*/  size; int /*<<< orphan*/  elems; } ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qstrcmp_dir ; 
 int /*<<< orphan*/  qstrcmp_plain ; 

void dir_list_sort(struct string_list *list, bool dir_first)
{
   if (list)
      qsort(list->elems, list->size, sizeof(struct string_list_elem),
            dir_first ? qstrcmp_dir : qstrcmp_plain);
}