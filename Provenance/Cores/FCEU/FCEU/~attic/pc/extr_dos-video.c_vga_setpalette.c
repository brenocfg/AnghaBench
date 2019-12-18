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
 int /*<<< orphan*/  outp (int,int) ; 

void vga_setpalette(int i, int r, int g, int b)
{ 
 outp(0x3c8,i);
 outp(0x3c9,r);
 outp(0x3c9,g);
 outp(0x3c9,b); 
}