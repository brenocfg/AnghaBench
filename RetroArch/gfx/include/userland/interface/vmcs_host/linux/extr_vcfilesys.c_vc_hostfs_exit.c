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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostfs_log_cat ; 
 int /*<<< orphan*/ * p_file_info_table ; 
 int /*<<< orphan*/  vcos_log_unregister (int /*<<< orphan*/ *) ; 

void vc_hostfs_exit(void)
{
   vcos_log_unregister(&hostfs_log_cat);
   if (p_file_info_table)
   {
      free(p_file_info_table);
      p_file_info_table = NULL;
   }
}