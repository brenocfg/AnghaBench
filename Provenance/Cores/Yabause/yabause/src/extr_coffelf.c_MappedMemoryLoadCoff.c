#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ physaddr; scalar_t__ virtaddr; scalar_t__ sectionsize; scalar_t__ sectionptr; scalar_t__ relptr; scalar_t__ linenoptr; int numreloc; int numlineno; scalar_t__ flags; } ;
typedef  TYPE_1__ u8 ;
typedef  size_t u32 ;
typedef  TYPE_1__ section_header_struct ;
struct TYPE_13__ {int numsections; scalar_t__ timedate; scalar_t__ symtabptr; scalar_t__ numsymtabs; int optheader; int flags; int* magic; } ;
typedef  TYPE_3__ coff_header_struct ;
typedef  int /*<<< orphan*/  coff_header ;
struct TYPE_14__ {int versionstamp; scalar_t__ textsize; scalar_t__ datasize; scalar_t__ bsssize; scalar_t__ entrypoint; scalar_t__ textaddr; scalar_t__ dataaddr; } ;
typedef  TYPE_4__ aout_header_struct ;
typedef  int /*<<< orphan*/  aout_header ;
struct TYPE_16__ {scalar_t__ PC; } ;
struct TYPE_15__ {TYPE_7__ regs; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DoubleWordSwap (scalar_t__) ; 
 TYPE_6__* MSH2 ; 
 int /*<<< orphan*/  MappedMemoryWriteByte (scalar_t__,TYPE_1__) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SH2GetRegisters (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  SH2SetRegisters (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  SH2WriteNotify (scalar_t__,size_t) ; 
 int /*<<< orphan*/  WordSwap (int) ; 
 int /*<<< orphan*/  YabauseResetNoLoad () ; 
 int /*<<< orphan*/  YabauseSpeedySetup () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 

int MappedMemoryLoadCoff(const char *filename)
{
   coff_header_struct coff_header;
   aout_header_struct aout_header;
   section_header_struct *section_headers=NULL;
   FILE *fp;
   u8 *buffer;
   u32 i, j;
   size_t num_read = 0;

   if ((fp = fopen(filename, "rb")) == NULL)
      return -1;

   num_read = fread((void *)&coff_header, sizeof(coff_header), 1, fp);
#ifndef WORDS_BIGENDIAN
   WordSwap(coff_header.numsections);
   DoubleWordSwap(coff_header.timedate);
   DoubleWordSwap(coff_header.timedate);
   DoubleWordSwap(coff_header.symtabptr);
   DoubleWordSwap(coff_header.numsymtabs);
   WordSwap(coff_header.optheader);
   WordSwap(coff_header.flags);
#endif

   if (coff_header.magic[0] != 0x05 || coff_header.magic[1] != 0x00 ||
       coff_header.optheader != sizeof(aout_header))
   {
      // Not SH COFF or is missing the optional header
      fclose(fp);
      return -1;
   }

   num_read = fread((void *)&aout_header, sizeof(aout_header), 1, fp);
#ifndef WORDS_BIGENDIAN
   WordSwap(aout_header.versionstamp);
   DoubleWordSwap(aout_header.textsize);
   DoubleWordSwap(aout_header.datasize);
   DoubleWordSwap(aout_header.bsssize);
   DoubleWordSwap(aout_header.entrypoint);
   DoubleWordSwap(aout_header.textaddr);
   DoubleWordSwap(aout_header.dataaddr);
#endif

   // Read in each section header
   if ((section_headers = (section_header_struct *)malloc(sizeof(section_header_struct) * coff_header.numsections)) == NULL)
   {
      fclose(fp);
      return -2;
   }

   // read in section headers
   for (i = 0; i < coff_header.numsections; i++)
   {
      num_read = fread((void *)&section_headers[i], sizeof(section_header_struct), 1, fp);
#ifndef WORDS_BIGENDIAN
      DoubleWordSwap(section_headers[i].physaddr);
      DoubleWordSwap(section_headers[i].virtaddr);
      DoubleWordSwap(section_headers[i].sectionsize);
      DoubleWordSwap(section_headers[i].sectionptr);
      DoubleWordSwap(section_headers[i].relptr);
      DoubleWordSwap(section_headers[i].linenoptr);
      WordSwap(section_headers[i].numreloc);
      WordSwap(section_headers[i].numlineno);
      DoubleWordSwap(section_headers[i].flags);
#endif
   }

   YabauseResetNoLoad();

   // Setup the vector table area, etc.
   YabauseSpeedySetup();

   // Read in sections, load them to ram
   for (i = 0; i < coff_header.numsections; i++)
   {
      if (section_headers[i].sectionsize == 0 ||
          section_headers[i].sectionptr == 0)
         // Skip to the next section
         continue;
      
      if ((buffer = (u8 *)malloc(section_headers[i].sectionsize)) == NULL)
      {
         fclose(fp);
         free(section_headers);
         return -2;
      }

      fseek(fp, section_headers[i].sectionptr, SEEK_SET);
      num_read = fread((void *)buffer, 1, section_headers[i].sectionsize, fp);

      for (j = 0; j < section_headers[i].sectionsize; j++)
         MappedMemoryWriteByte(section_headers[i].physaddr+j, buffer[j]);
      SH2WriteNotify(section_headers[i].physaddr,
                     section_headers[i].sectionsize);

      free(buffer);
   }

   // Clean up
   free(section_headers);
   fclose(fp);

   SH2GetRegisters(MSH2, &MSH2->regs);
   MSH2->regs.PC = aout_header.entrypoint;
   SH2SetRegisters(MSH2, &MSH2->regs);
   return 0;
}