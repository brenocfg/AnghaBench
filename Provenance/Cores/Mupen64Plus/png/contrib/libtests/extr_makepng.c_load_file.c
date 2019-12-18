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
typedef  char* png_const_charp ;
typedef  scalar_t__** png_bytepp ;
typedef  scalar_t__* png_bytep ;
typedef  scalar_t__ png_byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__* malloc (size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * tmpfile () ; 

__attribute__((used)) static size_t
load_file(png_const_charp name, png_bytepp result)
{
   FILE *fp = tmpfile();

   if (fp != NULL)
   {
      FILE *ip = fopen(name, "rb");

      if (ip != NULL)
      {
         size_t total = 0;
         int ch;

         for (;;)
         {
            ch = getc(ip);
            if (ch == EOF) break;
            putc(ch, fp);
            ++total;
         }

         if (ferror(ip))
         {
            perror(name);
            fprintf(stderr, "%s: read error\n", name);
            (void)fclose(ip);
         }

         else
         {
            (void)fclose(ip);

            if (ferror(fp))
            {
               perror("temporary file");
               fprintf(stderr, "temporary file write error\n");
            }

            else
            {
               rewind(fp);

               if (total > 0)
               {
                  /* Round up to a multiple of 4 here to allow an iCCP profile
                   * to be padded to a 4x boundary.
                   */
                  png_bytep data = malloc((total+3)&~3);

                  if (data != NULL)
                  {
                     size_t new_size = 0;

                     for (;;)
                     {
                        ch = getc(fp);
                        if (ch == EOF) break;
                        data[new_size++] = (png_byte)ch;
                     }

                     if (ferror(fp) || new_size != total)
                     {
                        perror("temporary file");
                        fprintf(stderr, "temporary file read error\n");
                        free(data);
                     }

                     else
                     {
                        (void)fclose(fp);
                        *result = data;
                        return total;
                     }
                  }

                  else
                     fprintf(stderr, "%s: out of memory loading file\n", name);
               }

               else
                  fprintf(stderr, "%s: empty file\n", name);
            }
         }
      }

      else
      {
         perror(name);
         fprintf(stderr, "%s: open failed\n", name);
      }

      fclose(fp);
   }

   else
      fprintf(stderr, "makepng: %s: could not open temporary file\n", name);

   exit(1);
   return 0;
}