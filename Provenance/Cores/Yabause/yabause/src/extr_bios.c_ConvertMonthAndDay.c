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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MappedMemoryWriteByte (int,int) ; 

__attribute__((used)) static void ConvertMonthAndDay(u32 data, u32 monthaddr, u32 dayaddr, int type)
{
   int i;
   u16 monthtbl[11] = { 31, 31+28, 31+28+31, 31+28+31+30, 31+28+31+30+31,
                        31+28+31+30+31+30, 31+28+31+30+31+30+31,
                        31+28+31+30+31+30+31+31, 31+28+31+30+31+30+31+31+30,
                        31+28+31+30+31+30+31+31+30+31,
                        31+28+31+30+31+30+31+31+30+31+30 };

   if (data < monthtbl[0])
   {
      // Month
      MappedMemoryWriteByte(monthaddr, 1);

      // Day
      MappedMemoryWriteByte(dayaddr, (u8)(data + 1));
      return;
   }

   for (i = 1; i < 11; i++)
   {
      if (data <= monthtbl[i])
         break;
   }

   if (type == 1)
   {
      // Month
      MappedMemoryWriteByte(monthaddr, (u8)(i + 1));

      // Day
      if ((i + 1) == 2)
         MappedMemoryWriteByte(dayaddr, (u8)(data - monthtbl[(i - 1)] + 1));
      else
         MappedMemoryWriteByte(dayaddr, (u8)(data - monthtbl[(i - 1)]));
   }
   else
   {
      // Month
      MappedMemoryWriteByte(monthaddr, (u8)(i + 1));
      
      // Day
      MappedMemoryWriteByte(dayaddr, (u8)(data - monthtbl[(i - 1)] + 1));
   }
}