#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {char* itemnum; } ;

/* Variables and functions */
 int YabLoadState (char*) ; 
 TYPE_1__* cdip ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*,int) ; 

int YabLoadStateSlot(const char *dirpath, u8 slot)
{
   char filename[512];

   if (cdip == NULL)
      return -1;

#ifdef WIN32
   sprintf(filename, "%s\\%s_%03d.yss", dirpath, cdip->itemnum, slot);
#else
   sprintf(filename, "%s/%s_%03d.yss", dirpath, cdip->itemnum, slot);
#endif
   return YabLoadState(filename);
}