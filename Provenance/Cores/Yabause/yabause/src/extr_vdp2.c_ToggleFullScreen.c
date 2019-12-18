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
struct TYPE_2__ {int /*<<< orphan*/  (* Resize ) (int,int,int) ;scalar_t__ (* IsFullscreen ) () ;} ;

/* Variables and functions */
 TYPE_1__* VIDCore ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (int,int,int) ; 
 int /*<<< orphan*/  stub3 (int,int,int) ; 

void ToggleFullScreen(void)
{
   if (VIDCore->IsFullscreen())
   {
      VIDCore->Resize(320, 224, 0);
   }
   else
   {
      VIDCore->Resize(640, 480, 1);
   }
}