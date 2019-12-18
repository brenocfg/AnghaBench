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
struct TYPE_2__ {int* saw_table; int* square_table; int* tri_table; int* noise_table; } ;

/* Variables and functions */
 TYPE_1__ plfo ; 
 int rand () ; 

void fill_plfo_tables()
{
   int i;

   //saw
   for (i = 0; i < 256; i++)
   {
      if (i < 128)
         plfo.saw_table[i] = i;
      else
         plfo.saw_table[i] = -256 + i;
   }

   //square
   for (i = 0; i < 256; i++)
   {
      if (i < 128)
         plfo.square_table[i] = 127;
      else
         plfo.square_table[i] = -128;
   }

   //triangular
   for (i = 0; i < 256; i++)
   {
      if (i < 64)
         plfo.tri_table[i] = i * 2;
      else if (i < 192)
         plfo.tri_table[i] = 255 - (i * 2);
      else
         plfo.tri_table[i] = (i * 2) - 512;
   }

   //noise
   for (i = 0; i < 256; i++)
   {
      plfo.noise_table[i] = rand() & 0xff;
   }
}