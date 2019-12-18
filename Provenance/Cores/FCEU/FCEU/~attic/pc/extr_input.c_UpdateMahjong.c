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
 int /*<<< orphan*/ * MahjongButtons ; 
 int MahjongData ; 

__attribute__((used)) static void UpdateMahjong(void)
{
 int x;
        
 MahjongData=0;
 for(x=0;x<21;x++)
 {  
  if(DTestButton(&MahjongButtons[x]))
   MahjongData|=1<<x;
 }
}