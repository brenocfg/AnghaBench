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
 int* palettedbb ; 
 int* palettedbg ; 
 int* palettedbr ; 
 int /*<<< orphan*/  vga_setpalette (int,int,int,int) ; 

__attribute__((used)) static void FlushPalette(void)
{
 int x;
 for(x=0;x<256;x++)
 {
  int z=x;
  vga_setpalette(z,palettedbr[x]>>2,palettedbg[x]>>2,palettedbb[x]>>2);
 }
}