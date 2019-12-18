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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int INT_MAX ; 
 scalar_t__ vc_hostfs_totalspace64 (char const*) ; 

int vc_hostfs_totalspace(const char *inPath)
{
   int ret;
   int64_t totalSpace = vc_hostfs_totalspace64(inPath);

   // Saturate return value (need this in case we have a large file system)
   if (totalSpace > (int64_t) INT_MAX)
   {
      ret = INT_MAX;
   }
   else
   {
      ret = (int) totalSpace;
   }
   return ret;
}