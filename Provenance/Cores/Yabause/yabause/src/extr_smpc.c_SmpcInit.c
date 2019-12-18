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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int clocksync; scalar_t__ basetime; void* regionid; void* regionsetting; } ;
typedef  TYPE_1__ SmpcInternal ;
typedef  int /*<<< orphan*/  Smpc ;

/* Variables and functions */
 TYPE_1__* SmpcInternalVars ; 
 int /*<<< orphan*/ * SmpcRegs ; 
 void** SmpcRegsT ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int SmpcInit(u8 regionid, int clocksync, u32 basetime) {
   if ((SmpcRegsT = (u8 *) calloc(1, sizeof(Smpc))) == NULL)
      return -1;

   SmpcRegs = (Smpc *) SmpcRegsT;

   if ((SmpcInternalVars = (SmpcInternal *) calloc(1, sizeof(SmpcInternal))) == NULL)
      return -1;

   SmpcInternalVars->regionsetting = regionid;
   SmpcInternalVars->regionid = regionid;
   SmpcInternalVars->clocksync = clocksync;
   SmpcInternalVars->basetime = basetime ? basetime : time(NULL);

   return 0;
}