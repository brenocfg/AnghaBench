#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* ChangeVideoFormat ) (int) ;} ;
struct TYPE_3__ {scalar_t__ IsPal; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSP_CLOCK_INC_NTSC ; 
 int /*<<< orphan*/  SCSP_CLOCK_INC_PAL ; 
 TYPE_2__* SNDCore ; 
 int /*<<< orphan*/  scsp_clock_inc ; 
 int /*<<< orphan*/  stub1 (int) ; 
 TYPE_1__ yabsys ; 

int ScspChangeVideoFormat(int type)
{
   scsp_clock_inc = yabsys.IsPal ? SCSP_CLOCK_INC_PAL : SCSP_CLOCK_INC_NTSC;

   SNDCore->ChangeVideoFormat(type ? 50 : 60);

   return 0;
}