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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ (* Init ) (char*) ;int (* GetStatus ) () ;int (* ReadTOC ) (int /*<<< orphan*/ ) ;int (* ReadSectorFAD ) (int,scalar_t__) ;} ;

/* Variables and functions */
 TYPE_1__ ArchCD ; 
 char* COPYRIGHT_YEAR ; 
 int /*<<< orphan*/  IsTOCValid (int /*<<< orphan*/ ) ; 
 char* PROG_NAME ; 
 int /*<<< orphan*/  ProgramUsage () ; 
 char* VER_NAME ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdTOC ; 
 scalar_t__ cdbuffer ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ memcmp (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stub1 (char*) ; 
 int stub2 () ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 int stub4 (int,scalar_t__) ; 
 int stub5 (int,scalar_t__) ; 
 int /*<<< orphan*/  testspassed ; 

int main(int argc, char *argv[])
{
   char *cdrom_name = NULL;
   u32 f_size=0;
   int status;
   char syncheader[12] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                           0xFF, 0xFF, 0xFF, 0x00};

   atexit(cleanup);

#ifndef _arch_dreamcast
   if (argc != 2)
   {
      ProgramUsage();
   }

   printf("%s v%s - by Cyber Warrior X(c)%s\n", PROG_NAME, VER_NAME, COPYRIGHT_YEAR);

   cdrom_name = argv[1];
#endif

   if (ArchCD.Init(cdrom_name) != 0)
   {
      printf("CDInit error: Unable to initialize cdrom\n");
      exit(1);
   }
   else testspassed++;

   // Let's make sure we're returning the proper status
   status = ArchCD.GetStatus();

   if (status == 0 || status == 1)
   {
      testspassed++;

      if (ArchCD.ReadTOC(cdTOC) != (0xCC * 2))
      {
         printf("CDReadToc error: return value was not the correct size\n");
      }
      else testspassed++;

      // Make sure TOC is valid          
      if (!IsTOCValid(cdTOC))
      {
         printf("CDReadToc error: TOC data has some issues\n");
      }
      else testspassed++;

      // Read sector 0
      if (ArchCD.ReadSectorFAD(150, cdbuffer) != 1)
      {
         printf("CDReadSectorFAD error: Reading of LBA 0(FAD 150) returned false\n");
      }
      else testspassed++;

      // Check cdbuffer to make sure contents are correct
      if (memcmp(syncheader, cdbuffer, 12) != 0)
      {
         printf("CDReadSectorFAD error: LBA 0(FAD 150) read is missing sync header\n");
      }
      else testspassed++;

      // look for "SEGA SEGASATURN"
      if (memcmp("SEGA SEGASATURN", cdbuffer+0x10, 15) != 0)
      {
         printf("CDReadSectorFAD error: LBA 0(FAD 150)'s sector contents were not as expected\n");
      }
      else testspassed++;

      // Read sector 16(I figured it makes a good random test sector)
      if (ArchCD.ReadSectorFAD(166, cdbuffer) != 1)
      {
         printf("CDReadSectorFAD error: Reading of LBA 16(FAD 166) returned false\n");
      }
      else testspassed++;

      // Check cdbuffer to make sure contents are correct
      if (memcmp(syncheader, cdbuffer, 12) != 0)
      {
         printf("CDReadSectorFAD error: LBA 16(FAD 166) read is missing sync header\n");
      }
      else testspassed++;

      // look for "CD001"
      if (memcmp("CD001", cdbuffer+0x11, 5) != 0)
      {
         printf("CDReadSectorFAD error: LBA 16(FAD 166)'s sector contents were not as expected\n");
      }
      else testspassed++;
   }
   else
   {
      printf("CDGetStatus error: Can't continue the rest of the test - There's either no CD present or the tray is open\n");
      exit(1);
   }
}