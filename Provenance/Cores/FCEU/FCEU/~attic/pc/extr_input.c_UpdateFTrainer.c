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

/* Variables and functions */
 scalar_t__ DTestButton (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FTrainerButtons ; 
 int FTrainerData ; 

__attribute__((used)) static void UpdateFTrainer(void)
{
 int x;

 FTrainerData=0;

 for(x=0;x<12;x++)
 {
  if(DTestButton(&FTrainerButtons[x]))
   FTrainerData|=1<<x;
 }
}