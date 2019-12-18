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
typedef  enum core_info_list_qsort_type { ____Placeholder_core_info_list_qsort_type } core_info_list_qsort_type ;
typedef  int /*<<< orphan*/  core_info_t ;
struct TYPE_3__ {int count; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ core_info_list_t ;

/* Variables and functions */
#define  CORE_INFO_LIST_SORT_CORE_NAME 131 
#define  CORE_INFO_LIST_SORT_DISPLAY_NAME 130 
#define  CORE_INFO_LIST_SORT_PATH 129 
#define  CORE_INFO_LIST_SORT_SYSTEM_NAME 128 
 scalar_t__ core_info_qsort_func_core_name ; 
 scalar_t__ core_info_qsort_func_display_name ; 
 scalar_t__ core_info_qsort_func_path ; 
 scalar_t__ core_info_qsort_func_system_name ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int,int,int (*) (void const*,void const*)) ; 

void core_info_qsort(core_info_list_t *core_info_list,
      enum core_info_list_qsort_type qsort_type)
{
   if (!core_info_list)
      return;

   if (core_info_list->count < 2)
      return;

   switch (qsort_type)
   {
      case CORE_INFO_LIST_SORT_PATH:
         qsort(core_info_list->list,
               core_info_list->count,
               sizeof(core_info_t),
               (int (*)(const void *, const void *))
               core_info_qsort_func_path);
         break;
      case CORE_INFO_LIST_SORT_DISPLAY_NAME:
         qsort(core_info_list->list,
               core_info_list->count,
               sizeof(core_info_t),
               (int (*)(const void *, const void *))
               core_info_qsort_func_display_name);
         break;
      case CORE_INFO_LIST_SORT_CORE_NAME:
         qsort(core_info_list->list,
               core_info_list->count,
               sizeof(core_info_t),
               (int (*)(const void *, const void *))
               core_info_qsort_func_core_name);
         break;
      case CORE_INFO_LIST_SORT_SYSTEM_NAME:
         qsort(core_info_list->list,
               core_info_list->count,
               sizeof(core_info_t),
               (int (*)(const void *, const void *))
               core_info_qsort_func_system_name);
         break;
      default:
         return;
   }
}