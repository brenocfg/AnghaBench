#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_9__ {int numblocks; int* blocknum; TYPE_6__** block; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ partition_struct ;
typedef  int /*<<< orphan*/  filter_struct ;
struct TYPE_10__ {int lba; int size; int /*<<< orphan*/  recordsize; } ;
typedef  TYPE_2__ dirrec_struct ;
struct TYPE_12__ {int getsectsize; scalar_t__ curdirsect; int curdirfidoffset; int curdirsize; int numfiles; TYPE_2__* fileinfo; int /*<<< orphan*/ * outconcddev; } ;
struct TYPE_11__ {int size; scalar_t__* data; } ;

/* Variables and functions */
 TYPE_8__* Cs2Area ; 
 int /*<<< orphan*/  Cs2CopyDirRecord (scalar_t__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Cs2FreeBlock (TYPE_6__*) ; 
 TYPE_1__* Cs2ReadUnFilteredSector (int) ; 
 int /*<<< orphan*/  Cs2SortBlocks (TYPE_1__*) ; 
 int MAX_FILES ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int Cs2ReadFileSystem(filter_struct * curfilter, u32 fid, int isoffset)
{
   u8 * workbuffer;
   u32 i;
   dirrec_struct dirrec;
   u8 numsectorsleft = 0;
   u32 curdirlba = 0;
   partition_struct * rfspartition;
   u32 blocksectsize = Cs2Area->getsectsize;

   Cs2Area->outconcddev = curfilter;

   if (isoffset)
   {
      // readDirectory operation

      // make sure we have a valid current directory
      if (Cs2Area->curdirsect == 0)
         return -1;

      Cs2Area->curdirfidoffset = fid - 2;
      curdirlba = Cs2Area->curdirsect;
      numsectorsleft = (u8)Cs2Area->curdirsize;
   }
   else
   {
      // changeDirectory operation

      if (fid == 0xFFFFFF)
      {
         // Figure out root directory's location

         // Read sector 16
         if ((rfspartition = Cs2ReadUnFilteredSector(166)) == NULL)
            return -2;

         blocksectsize = rfspartition->block[rfspartition->numblocks - 1]->size;

         // Retrieve directory record's lba
         Cs2CopyDirRecord(rfspartition->block[rfspartition->numblocks - 1]->data + 0x9C, &dirrec);

         // Free Block
         rfspartition->size -= rfspartition->block[rfspartition->numblocks - 1]->size;
         Cs2FreeBlock(rfspartition->block[rfspartition->numblocks - 1]);
         rfspartition->blocknum[rfspartition->numblocks - 1] = 0xFF;

         // Sort remaining blocks
         Cs2SortBlocks(rfspartition);
         rfspartition->numblocks -= 1;

         curdirlba = Cs2Area->curdirsect = dirrec.lba;
         Cs2Area->curdirsize = (dirrec.size / blocksectsize) - 1;
         numsectorsleft = (u8)Cs2Area->curdirsize;
         Cs2Area->curdirfidoffset = 0;
      }
      else
      {
         // Read in new directory record of specified directory

         // make sure we have a valid current directory
         if (Cs2Area->curdirsect == 0)
            return -1;

         curdirlba = Cs2Area->curdirsect = Cs2Area->fileinfo[fid - Cs2Area->curdirfidoffset].lba - 150;
         Cs2Area->curdirsize = (Cs2Area->fileinfo[fid - Cs2Area->curdirfidoffset].size / blocksectsize) - 1;
         numsectorsleft = (u8)Cs2Area->curdirsize;
         Cs2Area->curdirfidoffset = 0;
      }
   }

   // Make sure any old records are cleared
   memset(Cs2Area->fileinfo, 0, sizeof(dirrec_struct) * MAX_FILES);

   // now read in first sector of directory record
   if ((rfspartition = Cs2ReadUnFilteredSector(curdirlba+150)) == NULL)
      return -2;

   curdirlba++;
   workbuffer = rfspartition->block[rfspartition->numblocks - 1]->data;

   // Fill in first two entries of fileinfo
   for (i = 0; i < 2; i++)
   {
      Cs2CopyDirRecord(workbuffer, Cs2Area->fileinfo + i);
      Cs2Area->fileinfo[i].lba += 150;
      workbuffer += Cs2Area->fileinfo[i].recordsize;

      if (workbuffer[0] == 0)
      {
         Cs2Area->numfiles = i;
         break;
      }
   }

   // If doing a ReadDirectory operation, parse sector entries until we've
   // found the fid that matches fid
   if (isoffset)
   {
      for (i = 2; i < fid; i++)
      {
         Cs2CopyDirRecord(workbuffer, Cs2Area->fileinfo + 2);
         workbuffer += Cs2Area->fileinfo[2].recordsize;

         if (workbuffer[0] == 0)
         {
            if (numsectorsleft > 0)
            {
               // Free previous read sector
               rfspartition->size -= rfspartition->block[rfspartition->numblocks - 1]->size;
               Cs2FreeBlock(rfspartition->block[rfspartition->numblocks - 1]);
               rfspartition->blocknum[rfspartition->numblocks - 1] = 0xFF;

               // Sort remaining blocks
               Cs2SortBlocks(rfspartition);
               rfspartition->numblocks -= 1;

               // Read in next sector of directory record
               if ((rfspartition = Cs2ReadUnFilteredSector(curdirlba+150)) == NULL)
                  return -2;

               curdirlba++;

               numsectorsleft--;
               workbuffer = rfspartition->block[rfspartition->numblocks - 1]->data;
            }
            else
            {
               break;
            }
         }
      }
   }

   // Now generate the last 254 entries(the first two should've already been
   // generated earlier)
   for (i = 2; i < MAX_FILES; i++)
   {
      Cs2CopyDirRecord(workbuffer, Cs2Area->fileinfo + i);
      Cs2Area->fileinfo[i].lba += 150;
      workbuffer += Cs2Area->fileinfo[i].recordsize;

      if (workbuffer[0] == 0)
      {
         if (numsectorsleft > 0)
         {
            // Free previous read sector
            rfspartition->size -= rfspartition->block[rfspartition->numblocks - 1]->size;
            Cs2FreeBlock(rfspartition->block[rfspartition->numblocks - 1]);
            rfspartition->blocknum[rfspartition->numblocks - 1] = 0xFF;

            // Sort remaining blocks
            Cs2SortBlocks(rfspartition);
            rfspartition->numblocks -= 1;

            // Read in next sector of directory record
            if ((rfspartition = Cs2ReadUnFilteredSector(curdirlba+150)) == NULL)
               return -2;

            curdirlba++;
            numsectorsleft--;
            workbuffer = rfspartition->block[rfspartition->numblocks - 1]->data;
         }
         else
         {
            Cs2Area->numfiles = i;
            break;
         }
      }
   }

   // Free the remaining sector
   rfspartition->size -= rfspartition->block[rfspartition->numblocks - 1]->size;
   Cs2FreeBlock(rfspartition->block[rfspartition->numblocks - 1]);
   rfspartition->blocknum[rfspartition->numblocks - 1] = 0xFF;

   // Sort remaining blocks
   Cs2SortBlocks(rfspartition);
   rfspartition->numblocks -= 1;

//#if CDDEBUG
//  for (i = 0; i < MAX_FILES; i++)
//  {
//     CDLOG("fileinfo[%d].name = %s\n", i, Cs2Area->fileinfo[i].name);
//  }
//#endif

  return 0;
}