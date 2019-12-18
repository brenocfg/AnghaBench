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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_one_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 

int main(int argc, char **argv)
{
   int err = 0;

   printf("/* adler32, crc32, MD5[16], intent, date, length, file-name */\n");

   if (argc > 1)
   {
      int i;

      for (i=1; i<argc; ++i)
      {
         FILE *ip = fopen(argv[i], "rb");

         if (ip == NULL || !read_one_file(ip, argv[i]))
         {
            err = 1;
            perror(argv[i]);
            fprintf(stderr, "%s: read error\n", argv[i]);
            printf("/* ERROR: %s */\n", argv[i]);
         }

         (void)fclose(ip);
      }
   }

   else
   {
      if (!read_one_file(stdin, "-"))
      {
         err = 1;
         perror("stdin");
         fprintf(stderr, "stdin: read error\n");
         printf("/* ERROR: stdin */\n");
      }
   }

   return err;
}