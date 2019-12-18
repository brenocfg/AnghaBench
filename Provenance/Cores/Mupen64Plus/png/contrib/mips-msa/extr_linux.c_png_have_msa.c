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
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_warning (int /*<<< orphan*/ ,char*) ; 
 int strcmp (char*,char*) ; 

__attribute__((used)) static int
png_have_msa(png_structp png_ptr)
{
   FILE *f = fopen("/proc/cpuinfo", "rb");

   char *string = "msa";
   char word[10];

   if (f != NULL)
   {
      while(!feof(f))
      {
         int ch = fgetc(f);
         static int i = 0;

         while(!(ch <= 32))
         {
            word[i++] = ch;
            ch = fgetc(f);
         }

         int val = strcmp(string, word);

         if (val == 0)
            return 1;

         i = 0;
         memset(word, 0, 10);
      }

      fclose(f);
   }
#ifdef PNG_WARNINGS_SUPPORTED
   else
      png_warning(png_ptr, "/proc/cpuinfo open failed");
#endif
   return 0;
}