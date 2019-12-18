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
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  char* png_bytep ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* extract (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fwrite (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* no_profile ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 scalar_t__ remove (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
extract_one_file(const char *filename)
{
   int result = 0;
   FILE *fp = fopen(filename, "rb");

   if (fp != NULL)
   {
      png_uint_32 proflen = 0;
      png_bytep profile = extract(fp, &proflen);

      if (profile != NULL && profile != no_profile)
      {
         size_t len;
         char *output;

         {
            const char *ep = strrchr(filename, '.');

            if (ep != NULL)
               len = ep-filename;

            else
               len = strlen(filename);
         }

         output = malloc(len + 5);
         if (output != NULL)
         {
            FILE *of;

            memcpy(output, filename, len);
            strcpy(output+len, ".icc");

            of = fopen(output, "wb");
            if (of != NULL)
            {
               if (fwrite(profile, proflen, 1, of) == 1 &&
                  fflush(of) == 0 &&
                  fclose(of) == 0)
               {
                  if (verbose)
                     printf("%s -> %s\n", filename, output);
                  /* Success return */
                  result = 1;
               }

               else
               {
                  fprintf(stderr, "%s: error writing profile\n", output);
                  if (remove(output))
                     fprintf(stderr, "%s: could not remove file\n", output);
               }
            }

            else
               fprintf(stderr, "%s: failed to open output file\n", output);

            free(output);
         }

         else
            fprintf(stderr, "%s: OOM allocating string!\n", filename);

         free(profile);
      }

      else if (verbose && profile == no_profile)
	printf("%s has no profile\n", filename);
   }

   else
      fprintf(stderr, "%s: could not open file\n", filename);

   return result;
}