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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  T1WriteByte (void*,int,int) ; 

void FormatBackupRam(void *mem, u32 size)
{
   int i, i2;
   u32 i3;
   u8 header[32] = {
      0xFF, 'B', 0xFF, 'a', 0xFF, 'c', 0xFF, 'k',
      0xFF, 'U', 0xFF, 'p', 0xFF, 'R', 0xFF, 'a',
      0xFF, 'm', 0xFF, ' ', 0xFF, 'F', 0xFF, 'o',
      0xFF, 'r', 0xFF, 'm', 0xFF, 'a', 0xFF, 't'
   };

   // Fill in header
   for(i2 = 0; i2 < 4; i2++)
      for(i = 0; i < 32; i++)
         T1WriteByte(mem, (i2 * 32) + i, header[i]);

   // Clear the rest
   for(i3 = 0x80; i3 < size; i3+=2)
   {
      T1WriteByte(mem, i3, 0xFF);
      T1WriteByte(mem, i3+1, 0x00);
   }
}