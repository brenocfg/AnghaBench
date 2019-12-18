#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  PC; } ;
struct TYPE_6__ {TYPE_2__ regs; } ;

/* Variables and functions */
 TYPE_1__* MSH2 ; 
 int /*<<< orphan*/  MappedMemoryLoad (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MappedMemoryLoadCoff (char const*) ; 
 int /*<<< orphan*/  MappedMemoryLoadElf (char const*) ; 
 int /*<<< orphan*/  SH2GetRegisters (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SH2SetRegisters (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  YabauseResetNoLoad () ; 
 int /*<<< orphan*/  YabauseSpeedySetup () ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 
 char* strrchr (char const*,char) ; 
 char toupper (char) ; 

void MappedMemoryLoadExec(const char *filename, u32 pc)
{
   char *p;
   size_t i;

   if ((p = strrchr(filename, '.')))
   {
      p = strdup(p);
      for (i = 0; i < strlen(p); i++)
         p[i] = toupper(p[i]);
      if (strcmp(p, ".COF") == 0 || strcmp(p, ".COFF") == 0)
      {
         MappedMemoryLoadCoff(filename);
         free(p);
         return;
      }
      else if(strcmp(p, ".ELF") == 0)
      {
         MappedMemoryLoadElf(filename);
         free(p);
         return;
      }

      free(p);
   }

   YabauseResetNoLoad();

   // Setup the vector table area, etc.
   YabauseSpeedySetup();

   MappedMemoryLoad(filename, pc);
   SH2GetRegisters(MSH2, &MSH2->regs);
   MSH2->regs.PC = pc;
   SH2SetRegisters(MSH2, &MSH2->regs);
}