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
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ path_stat_cb (char const*,int*) ; 

int32_t path_get_size(const char *path)
{
   int32_t filesize = 0;
   if (path_stat_cb(path, &filesize) != 0)
      return filesize;

   return -1;
}