#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pixel_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* DisplayMessage ) (TYPE_1__*,int /*<<< orphan*/ *,int,int) ;} ;
struct TYPE_4__ {scalar_t__ timeleft; scalar_t__ hidden; int /*<<< orphan*/  message; } ;

/* Variables and functions */
 TYPE_3__* OSD ; 
 int OSDMSG_COUNT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* osdmessages ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

int OSDDisplayMessages(pixel_t * buffer, int w, int h)
{
   int i = 0;
   int somethingnew = 0;

   if (OSD == NULL) return somethingnew;

   for(i = 0;i < OSDMSG_COUNT;i++)
      if (osdmessages[i].timeleft > 0)
      {
         if (osdmessages[i].hidden == 0)
         {
            somethingnew = 1;
            OSD->DisplayMessage(osdmessages + i, buffer, w, h);
         }
         osdmessages[i].timeleft--;
         if (osdmessages[i].timeleft == 0) free(osdmessages[i].message);
      }

   return somethingnew;
}