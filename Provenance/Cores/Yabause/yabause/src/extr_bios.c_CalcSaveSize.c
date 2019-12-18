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
typedef  int u16 ;

/* Variables and functions */
 int MappedMemoryReadByte (int) ; 

__attribute__((used)) static int CalcSaveSize(u32 tableaddr, int blocksize)
{
   int numblocks=0;

   // Now figure out how many blocks this save is
   for(;;)
   {
       u16 block;
       block = (MappedMemoryReadByte(tableaddr) << 8) | MappedMemoryReadByte(tableaddr + 2);
       if (block == 0)
         break;
       tableaddr += 4;
       if (((tableaddr-1) & ((blocksize << 1) - 1)) == 0)
          tableaddr += 8;
       numblocks++;
   }

   return numblocks;
}