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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ CheckHeader (int) ; 
 int GetDeviceStats (int,int*,int*,int*) ; 
 int GetFreeSpace (int,int,int,int) ; 

int BupGetStats(u32 device, u32 *freespace, u32 *maxspace)
{
   u32 ret;
   u32 size;
   u32 addr;
   u32 blocksize;

   ret = GetDeviceStats(device, &size, &addr, &blocksize);

   // Make sure there's a proper header, and return if there's any other errors
   if (ret == 1 || CheckHeader(device) != 0)
      return 0;

   *maxspace = size / blocksize;
   *freespace = GetFreeSpace(device, size, addr, blocksize);

   return 1;
}