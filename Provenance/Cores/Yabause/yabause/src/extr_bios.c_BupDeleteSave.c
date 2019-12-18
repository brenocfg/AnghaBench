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
 int /*<<< orphan*/  DeleteSave (int,int,int) ; 
 int FindSave2 (int,char const*,int,int,int,int) ; 
 int GetDeviceStats (int,int*,int*,int*) ; 

int BupDeleteSave(u32 device, const char *savename)
{
   u32 ret;
   u32 size;
   u32 addr;
   u32 blocksize;
   u32 block;

   ret = GetDeviceStats(device, &size, &addr, &blocksize);

   // Make sure there's a proper header, and return if there's any other errors
   if (ret == 1 || CheckHeader(device) != 0)
      return -1;

   // Let's find and delete the save game
   if ((block = FindSave2(device, savename, 2, size, addr, blocksize)) != 0)
   {
      // Delete old save
      DeleteSave(addr, block, blocksize);
      return 0;
   }

   return -2;
}