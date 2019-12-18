#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ all; } ;
struct TYPE_7__ {scalar_t__* R; scalar_t__ PC; scalar_t__ PR; scalar_t__ MACL; scalar_t__ MACH; scalar_t__ VBR; scalar_t__ GBR; TYPE_1__ SR; } ;
struct TYPE_6__ {int /*<<< orphan*/  isslave; TYPE_4__ regs; } ;
typedef  TYPE_2__ SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/  AllocAmendPrintString (char*,void const*) ; 
 int /*<<< orphan*/  SH2GetRegisters (TYPE_2__*,TYPE_4__*) ; 
#define  YAB_ERR_CANNOTINIT 138 
#define  YAB_ERR_FILENOTFOUND 137 
#define  YAB_ERR_FILEREAD 136 
#define  YAB_ERR_FILEWRITE 135 
#define  YAB_ERR_MEMORYALLOC 134 
#define  YAB_ERR_OTHER 133 
#define  YAB_ERR_SDL 132 
#define  YAB_ERR_SH2INVALIDOPCODE 131 
#define  YAB_ERR_SH2READ 130 
#define  YAB_ERR_SH2WRITE 129 
#define  YAB_ERR_UNKNOWN 128 
 int /*<<< orphan*/  YuiErrorMsg (char*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long) ; 

void YabSetError(int type, const void *extra)
{
   char tempstr[512];
   SH2_struct *sh;

   switch (type)
   {
      case YAB_ERR_FILENOTFOUND:
         AllocAmendPrintString(_("File not found: "), extra);
         break;
      case YAB_ERR_MEMORYALLOC:
         YuiErrorMsg(_("Error allocating memory\n"));
         break;
      case YAB_ERR_FILEREAD:
         AllocAmendPrintString(_("Error reading file: "), extra);
         break;
      case YAB_ERR_FILEWRITE:
         AllocAmendPrintString(_("Error writing file: "), extra);
         break;
      case YAB_ERR_CANNOTINIT:
         AllocAmendPrintString(_("Cannot initialize "), extra);
         break;
      case YAB_ERR_SH2INVALIDOPCODE:
         sh = (SH2_struct *)extra;
         SH2GetRegisters(sh, &sh->regs);
         sprintf(tempstr, "%s SH2 invalid opcode\n\n"
                          "R0 =  %08lX\tR12 =  %08lX\n"
                          "R1 =  %08lX\tR13 =  %08lX\n"
                          "R2 =  %08lX\tR14 =  %08lX\n"
                          "R3 =  %08lX\tR15 =  %08lX\n"
                          "R4 =  %08lX\tSR =   %08lX\n"
                          "R5 =  %08lX\tGBR =  %08lX\n"
                          "R6 =  %08lX\tVBR =  %08lX\n"
                          "R7 =  %08lX\tMACH = %08lX\n"
                          "R8 =  %08lX\tMACL = %08lX\n"
                          "R9 =  %08lX\tPR =   %08lX\n"
                          "R10 = %08lX\tPC =   %08lX\n"
                          "R11 = %08lX\n", sh->isslave ? "Slave" : "Master",
                          (long)sh->regs.R[0], (long)sh->regs.R[12],
                          (long)sh->regs.R[1], (long)sh->regs.R[13],
                          (long)sh->regs.R[2], (long)sh->regs.R[14],
                          (long)sh->regs.R[3], (long)sh->regs.R[15],
                          (long)sh->regs.R[4], (long)sh->regs.SR.all,
                          (long)sh->regs.R[5], (long)sh->regs.GBR,
                          (long)sh->regs.R[6], (long)sh->regs.VBR,
                          (long)sh->regs.R[7], (long)sh->regs.MACH,
                          (long)sh->regs.R[8], (long)sh->regs.MACL,
                          (long)sh->regs.R[9], (long)sh->regs.PR,
                          (long)sh->regs.R[10], (long)sh->regs.PC,
                          (long)sh->regs.R[11]);
         YuiErrorMsg(tempstr);
         break;
      case YAB_ERR_SH2READ:
         YuiErrorMsg(_("SH2 read error\n")); // fix me
         break;
      case YAB_ERR_SH2WRITE:
         YuiErrorMsg(_("SH2 write error\n")); // fix me
         break;
      case YAB_ERR_SDL:
         AllocAmendPrintString(_("SDL Error: "), extra);
         break;
      case YAB_ERR_OTHER:
         YuiErrorMsg((char *)extra);
         break;
      case YAB_ERR_UNKNOWN:
      default:
         YuiErrorMsg(_("Unknown error occurred\n"));
         break;
   }
}