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
typedef  int /*<<< orphan*/  fpos_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fgetpos (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fsetpos (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ read_png (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int add_one_file(FILE *fp, char *name)
{
   FILE *ip = fopen(name, "rb");

   if (ip != NULL)
   {
      /* Read the file using libpng; this detects errors and also deals with
       * files which contain data beyond the end of the file.
       */
      int ok = 0;
      fpos_t pos;

      if (fgetpos(fp, &pos))
      {
         /* Fatal error reading the start: */
         perror("temporary file");
         fprintf(stderr, "temporary file fgetpos error\n");
         exit(1);
      }

      if (read_png(ip, -1/*by row*/, fp/*output*/))
      {
         if (ferror(ip))
         {
            perror(name);
            fprintf(stderr, "%s: read error\n", name);
         }

         else
            ok = 1; /* read ok */
      }

      else
         fprintf(stderr, "%s: file not added\n", name);

      (void)fclose(ip);

      /* An error in the output is fatal; exit immediately: */
      if (ferror(fp))
      {
         perror("temporary file");
         fprintf(stderr, "temporary file write error\n");
         exit(1);
      }

      if (ok)
         return 1;

      /* Did not read the file successfully, simply rewind the temporary
       * file.  This must happen after the ferror check above to avoid clearing
       * the error.
       */
      if (fsetpos(fp, &pos))
      {
         perror("temporary file");
         fprintf(stderr, "temporary file fsetpos error\n");
         exit(1);
      }
   }

   else
   {
      /* file open error: */
      perror(name);
      fprintf(stderr, "%s: open failed\n", name);
   }

   return 0; /* file not added */
}