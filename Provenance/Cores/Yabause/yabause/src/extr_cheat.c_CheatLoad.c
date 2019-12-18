#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  cheatlist_struct ;
struct TYPE_7__ {int type; int addr; int val; int enable; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CheatChangeDescriptionByIndex (int,char*) ; 
 int /*<<< orphan*/  CheatClearCodes () ; 
 int /*<<< orphan*/  DoubleWordSwap (int) ; 
 TYPE_3__* cheatlist ; 
 int cheatsize ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int numcheats ; 
 TYPE_3__* realloc (TYPE_3__*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  yread (TYPE_1__*,void*,int,int,int /*<<< orphan*/ *) ; 

int CheatLoad(const char *filename)
{
   FILE *fp;
   int i;
   char id[4];
   char desc[256];
   IOCheck_struct check = { 0, 0 };

   if (!filename)
      return -1;

   if ((fp = fopen(filename, "rb")) == NULL)
      return -1;

   yread(&check, (void *)id, 1, 4, fp);
   if (strncmp(id, "YCHT", 4) != 0)
   {
      fclose(fp);
      return -2;
   }

   CheatClearCodes();

   yread(&check, (void *)&numcheats, sizeof(int), 1, fp);
#ifndef WORDS_BIGENDIAN
   DoubleWordSwap(numcheats);
#endif

   if (numcheats >= cheatsize)
   {
      cheatlist = realloc(cheatlist, sizeof(cheatlist_struct) * (cheatsize * 2));
      memset((void *)cheatlist, 0, sizeof(cheatlist_struct) * (cheatsize * 2));
      cheatsize *= 2;
   }

   for(i = 0; i < numcheats; i++)
   {
      u8 descsize;

      yread(&check, (void *)&cheatlist[i].type, sizeof(int), 1, fp);
      yread(&check, (void *)&cheatlist[i].addr, sizeof(u32), 1, fp);
      yread(&check, (void *)&cheatlist[i].val, sizeof(u32), 1, fp);
      yread(&check, (void *)&descsize, sizeof(u8), 1, fp);
      yread(&check, (void *)desc, sizeof(char), descsize, fp);
      CheatChangeDescriptionByIndex(i, desc);
      yread(&check, (void *)&cheatlist[i].enable, sizeof(int), 1, fp);
#ifndef WORDS_BIGENDIAN
      DoubleWordSwap(cheatlist[i].type);
      DoubleWordSwap(cheatlist[i].addr);
      DoubleWordSwap(cheatlist[i].val);
      DoubleWordSwap(cheatlist[i].enable);
#endif
   }

   fclose (fp);

   return 0;
}