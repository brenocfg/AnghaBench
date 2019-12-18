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
struct TYPE_2__ {scalar_t__ emulatebios; scalar_t__ usequickload; scalar_t__ playing_ssf; } ;

/* Variables and functions */
 int /*<<< orphan*/  YAB_ERR_CANNOTINIT ; 
 int /*<<< orphan*/  YabSetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ YabauseQuickLoadGame () ; 
 int /*<<< orphan*/  YabauseResetNoLoad () ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__ yabsys ; 

void YabauseReset(void) {

   if (yabsys.playing_ssf)
      yabsys.playing_ssf = 0;

   YabauseResetNoLoad();

   if (yabsys.usequickload || yabsys.emulatebios)
   {
      if (YabauseQuickLoadGame() != 0)
      {
         if (yabsys.emulatebios)
            YabSetError(YAB_ERR_CANNOTINIT, _("Game"));
         else
            YabauseResetNoLoad();
      }
   }
}