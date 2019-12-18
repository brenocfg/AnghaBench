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
struct TYPE_2__ {int hidden; } ;

/* Variables and functions */
 int /*<<< orphan*/ * OSD ; 
 int /*<<< orphan*/  OSDDeInit () ; 
 int /*<<< orphan*/  OSDInit (int) ; 
 size_t OSDMSG_DEBUG ; 
 size_t OSDMSG_FPS ; 
 TYPE_1__* osdmessages ; 

int OSDChangeCore(int coreid)
{
   int preservefps, fpshidden, dbghidden;

   preservefps = (OSD != NULL);
   fpshidden = osdmessages[OSDMSG_FPS].hidden;
   dbghidden = osdmessages[OSDMSG_DEBUG].hidden;

   OSDDeInit();
   OSDInit(coreid);

   if (preservefps)
   {
      osdmessages[OSDMSG_FPS].hidden = fpshidden;
      osdmessages[OSDMSG_DEBUG].hidden = dbghidden;
   }

   return 0;
}