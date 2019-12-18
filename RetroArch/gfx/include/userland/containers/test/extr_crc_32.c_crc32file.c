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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Boolean_T ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  Error_ ; 
 int /*<<< orphan*/  Success_ ; 
 int UPDC32 (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 

Boolean_T crc32file(char *name, uint32_t *crc, long *charcnt)
{
      register FILE *fin;
      register uint32_t oldcrc32;
      register int c;

      oldcrc32 = 0xFFFFFFFF; *charcnt = 0;
#ifdef MSDOS
      if ((fin=fopen(name, "rb"))==NULL)
#else
      if ((fin=fopen(name, "r"))==NULL)
#endif
      {
            perror(name);
            return Error_;
      }
      while ((c=getc(fin))!=EOF)
      {
            ++*charcnt;
            oldcrc32 = UPDC32(c, oldcrc32);
      }

      if (ferror(fin))
      {
            perror(name);
            *charcnt = -1;
      }
      fclose(fin);

      *crc = oldcrc32 = ~oldcrc32;

      return Success_;
}