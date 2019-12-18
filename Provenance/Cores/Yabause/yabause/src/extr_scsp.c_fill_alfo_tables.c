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
 TYPE_1__ alfo ; 
 int rand () ; 

void fill_alfo_tables()
{
   int i;

   //saw
   for (i = 0; i < 256; i++)
   {
      alfo.saw_table[i] = i;
   }

   //square
   for (i = 0; i < 256; i++)
   {
      if (i < 128)
         alfo.square_table[i] = 0;
      else
         alfo.square_table[i] = 0xff;
   }

   //triangular
   for (i = 0; i < 256; i++)
   {
      if (i < 128)
         alfo.tri_table[i] = i * 2;
      else
         alfo.tri_table[i] = 255 - (i * 2);
   }

   //noise
   for (i = 0; i < 256; i++)
   {
      alfo.noise_table[i] = rand() & 0xff;
   }
}