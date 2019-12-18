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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int type; int /*<<< orphan*/  addr; int /*<<< orphan*/  val; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
#define  CHEATTYPE_BYTEWRITE 132 
#define  CHEATTYPE_ENABLE 131 
#define  CHEATTYPE_LONGWRITE 130 
#define  CHEATTYPE_NONE 129 
#define  CHEATTYPE_WORDWRITE 128 
 int /*<<< orphan*/  MappedMemoryReadWord (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MappedMemoryWriteByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MappedMemoryWriteLong (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MappedMemoryWriteWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2WriteNotify (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cheatlist ; 

void CheatDoPatches(void)
{
   int i;

   for (i = 0; ; i++)
   {
      switch (cheatlist[i].type)
      {
         case CHEATTYPE_NONE:
            return;
         case CHEATTYPE_ENABLE:
            if (cheatlist[i].enable == 0)
               continue;
            if (MappedMemoryReadWord(cheatlist[i].addr) != cheatlist[i].val)
               return;
            break;
         case CHEATTYPE_BYTEWRITE:
            if (cheatlist[i].enable == 0)
               continue;
            MappedMemoryWriteByte(cheatlist[i].addr, (u8)cheatlist[i].val);
            SH2WriteNotify(cheatlist[i].addr, 1);
            break;
         case CHEATTYPE_WORDWRITE:
            if (cheatlist[i].enable == 0)
               continue;
            MappedMemoryWriteWord(cheatlist[i].addr, (u16)cheatlist[i].val);
            SH2WriteNotify(cheatlist[i].addr, 2);
            break;
         case CHEATTYPE_LONGWRITE:
            if (cheatlist[i].enable == 0)
               continue;
            MappedMemoryWriteLong(cheatlist[i].addr, cheatlist[i].val);
            SH2WriteNotify(cheatlist[i].addr, 4);
            break;            
      }
   }
}