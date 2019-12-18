#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tilInfo_struct ;
struct TYPE_10__ {scalar_t__ addr; int count; } ;
struct TYPE_8__ {int num; int maxNum; TYPE_4__* match; scalar_t__ enabled; } ;
struct TYPE_7__ {scalar_t__ PC; } ;
struct TYPE_9__ {int instruction; TYPE_2__ trackInfLoop; TYPE_1__ regs; } ;
typedef  TYPE_3__ SH2_struct ;

/* Variables and functions */
 TYPE_4__* realloc (TYPE_4__*,int) ; 

void SH2HandleTrackInfLoop(SH2_struct *context)
{
   if (context->trackInfLoop.enabled)
   {
      // Look for specific bf/bt/bra instructions that branch to address < PC
      if ((context->instruction & 0x8B80) == 0x8B80 || // bf
          (context->instruction & 0x8F80) == 0x8F80 || // bf/s 
          (context->instruction & 0x8980) == 0x8980 || // bt
          (context->instruction & 0x8D80) == 0x8D80 || // bt/s 
          (context->instruction & 0xA800) == 0xA800)   // bra
      {
         int i;

         // See if it's already on match list
         for (i = 0; i < context->trackInfLoop.num; i++)
         {
            if (context->regs.PC == context->trackInfLoop.match[i].addr)
            {
               context->trackInfLoop.match[i].count++;
               return;
            }
         }

         if (context->trackInfLoop.num >= context->trackInfLoop.maxNum)
         {
            context->trackInfLoop.match = realloc(context->trackInfLoop.match, sizeof(tilInfo_struct) * (context->trackInfLoop.maxNum * 2));
            context->trackInfLoop.maxNum *= 2;
         }

         // Add new
         i=context->trackInfLoop.num;
         context->trackInfLoop.match[i].addr = context->regs.PC;
         context->trackInfLoop.match[i].count = 1;
         context->trackInfLoop.num++;
      }
   }
}