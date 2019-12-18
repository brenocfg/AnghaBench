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
typedef  int u16 ;
struct TYPE_2__ {int mcieb; int scieb; scalar_t__ scipd; scalar_t__ mcipd; } ;

/* Variables and functions */
 int SCSP_INTTARGET_MAIN ; 
 int SCSP_INTTARGET_SOUND ; 
 int /*<<< orphan*/  ScspRaiseInterrupt (int,int) ; 
 TYPE_1__ scsp ; 

__attribute__((used)) static void ScspCheckInterrupts(u16 mask, int target)
{
   int i;

   for (i = 0; i < 11; i++)
   {
      if ((1<<i) & mask & scsp.mcieb && scsp.mcipd)
         ScspRaiseInterrupt(i, SCSP_INTTARGET_MAIN & target);
      if ((1<<i) & mask & scsp.scieb && scsp.scipd)
         ScspRaiseInterrupt(i, SCSP_INTTARGET_SOUND & target);
   }
}