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
struct TYPE_3__ {int /*<<< orphan*/  hnd; } ;
typedef  TYPE_1__ winraw_mouse_t ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ GetRawInputDeviceInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,char*) ; 
 int /*<<< orphan*/  RIDI_DEVICENAME ; 

__attribute__((used)) static void winraw_log_mice_info(winraw_mouse_t *mice, unsigned mouse_cnt)
{
   unsigned i;
   char name[256];
   UINT name_size = sizeof(name);

   name[0] = '\0';

   for (i = 0; i < mouse_cnt; ++i)
   {
      UINT r = GetRawInputDeviceInfoA(mice[i].hnd, RIDI_DEVICENAME,
            name, &name_size);
      if (r == (UINT)-1 || r == 0)
         name[0] = '\0';
      RARCH_LOG("[WINRAW]: Mouse #%u %s.\n", i, name);
   }
}