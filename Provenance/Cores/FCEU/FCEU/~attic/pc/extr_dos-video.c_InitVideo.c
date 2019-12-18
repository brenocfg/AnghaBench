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
 int /*<<< orphan*/  DOSMemSet (int,int,int) ; 
 int FCEUDvmode ; 
 int /*<<< orphan*/  FlushPalette () ; 
 int /*<<< orphan*/  G320x200x256 ; 
 int ScreenLoc ; 
 int /*<<< orphan*/  SetBorder () ; 
 int /*<<< orphan*/  TweakVGA (int) ; 
 int /*<<< orphan*/  vga_setmode (int /*<<< orphan*/ ) ; 
 int vidready ; 

int InitVideo(void)
{
 vidready=0;
 switch(FCEUDvmode)
 {
  default:
  case 1:
  case 2:
  case 3:
  case 6:
  case 8:
         vga_setmode(G320x200x256);
	 vidready|=1;
         ScreenLoc=0xa0000;
         TweakVGA(FCEUDvmode);
         SetBorder();
         DOSMemSet(ScreenLoc, 128, 256*256);
         break;
 }
 vidready|=2;
 FlushPalette();
 return 1;
}