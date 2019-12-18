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
 int inportb (int) ; 

__attribute__((used)) static void vga_vsync(void)
{
   /* wait until any previous retrace has ended */
   do
   {
   }while (inportb(0x3da) & 8);

   /* wait until a new retrace has just begun */
   do
   {
   }while (!(inportb(0x3da) & 8));
}