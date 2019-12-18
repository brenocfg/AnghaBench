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
typedef  int int64_t ;
struct TYPE_3__ {scalar_t__ first_sector; int pos; } ;
typedef  TYPE_1__ cdfs_file_t ;

/* Variables and functions */

int64_t cdfs_tell(cdfs_file_t* file)
{
   if (!file || file->first_sector < 0)
      return -1;

   return file->pos;
}