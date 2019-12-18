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
 int /*<<< orphan*/  FCEUI_Sound (int) ; 
 int InitSB (int,int) ; 
 scalar_t__ f8bit ; 
 int soundo ; 

int InitSound(void)
{
 if(soundo)
 {
  if(soundo==1)
   soundo=44100;
  soundo=InitSB(soundo,f8bit?0:1);
  FCEUI_Sound(soundo);
 }
 return(soundo);
}