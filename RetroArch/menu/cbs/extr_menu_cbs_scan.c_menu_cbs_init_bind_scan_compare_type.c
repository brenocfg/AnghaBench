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
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_SCAN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  FILE_TYPE_CARCHIVE 132 
#define  FILE_TYPE_DIRECTORY 131 
#define  FILE_TYPE_NONE 130 
#define  FILE_TYPE_PLAIN 129 
#define  FILE_TYPE_RPL_ENTRY 128 
 int /*<<< orphan*/  action_scan_directory ; 
 int /*<<< orphan*/  action_scan_file ; 
 int /*<<< orphan*/  action_switch_thumbnail ; 

__attribute__((used)) static int menu_cbs_init_bind_scan_compare_type(menu_file_list_cbs_t *cbs,
      unsigned type)
{

   switch (type)
   {
#ifdef HAVE_LIBRETRODB
      case FILE_TYPE_DIRECTORY:
         BIND_ACTION_SCAN(cbs, action_scan_directory);
         return 0;
      case FILE_TYPE_CARCHIVE:
      case FILE_TYPE_PLAIN:
         BIND_ACTION_SCAN(cbs, action_scan_file);
         return 0;
#endif
      case FILE_TYPE_RPL_ENTRY:
         BIND_ACTION_SCAN(cbs, action_switch_thumbnail);
         break;

      case FILE_TYPE_NONE:
      default:
         break;
   }

   return -1;
}