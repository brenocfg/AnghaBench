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
typedef  size_t u16 ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int MappedMemoryReadByte (int) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 *GetFreeBlocks(u32 addr, u32 blocksize, u32 numblocks, u32 size)
{
   u8 *blocktbl;
   u16 *freetbl;
   u32 tableaddr;
   u32 i;
   u32 blockcount=0;

   // Create a table that tells us which blocks are free and used
   if ((blocktbl = (u8 *)malloc(sizeof(u8) * (size / blocksize))) == NULL)
      return NULL;

   memset(blocktbl, 0, (size / blocksize));

   for (i = ((2 * blocksize) << 1); i < (size << 1); i += (blocksize << 1))
   {
      // Find a block with the start of a save
      if (((s8)MappedMemoryReadByte(addr + i + 1)) < 0)
      {
         tableaddr = addr+i+0x45;
         blocktbl[i / (blocksize << 1)] = 1;

         // Now let's figure out which blocks are used
         for(;;)
         {
            u16 block;
            block = (MappedMemoryReadByte(tableaddr) << 8) | MappedMemoryReadByte(tableaddr + 2);
            if (block == 0)
               break;
            tableaddr += 4;
            if (((tableaddr-1) & ((blocksize << 1) - 1)) == 0)
               tableaddr += 8;
            // block is used
            blocktbl[block] = 1;
         }
      }
   }

   if ((freetbl = (u16 *)malloc(sizeof(u16) * numblocks)) == NULL)
   {
      free(blocktbl);
      return NULL;
   }

   // Find some free blocks for us to use
   for (i = 2; i < (size / blocksize); i++)
   {
      if (blocktbl[i] == 0)
      {
         freetbl[blockcount] = (u16)i;
         blockcount++;

         if (blockcount >= numblocks)
            break;
      }
   }

   // Ok, we're all done
   free(blocktbl);

   return freetbl;
}