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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 SNDWavGetAudioSpace(void)
{
   /* A "hack" to get sound core working enough
    * so videos are not "freezing". Values have been
    * found by experiments... I don't have a clue why
    * they are working ^^;
    */
   static int i = 0;
   i++;
   if (i == 55) {
      i = 0;
      return 85;
   } else {
      return 0;
   }
}