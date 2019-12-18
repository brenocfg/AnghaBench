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
struct SHA1Context {int* Message_Digest; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Input (struct SHA1Context*,char*,int) ; 
 int /*<<< orphan*/  SHA1Reset (struct SHA1Context*) ; 
 int /*<<< orphan*/  SHA1Result (struct SHA1Context*) ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 char fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,char*) ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
   struct SHA1Context sha;         /* SHA-1 context                 */
   FILE        *fp;                /* File pointer for reading files*/
   char        c;                  /* Character read from file      */
   int         i;                  /* Counter                       */
   int         reading_stdin;      /* Are we reading standard in?   */
   int         read_stdin = 0;     /* Have we read stdin?           */

   /*
    *  Check the program arguments and print usage information if -?
    *  or --help is passed as the first argument.
    */
   if (argc > 1 && (string_is_equal(argv[1],"-?") ||
            string_is_equal(argv[1],"--help")))
   {
      usage();
      return 1;
   }

   /*
    *  For each filename passed in on the command line, calculate the
    *  SHA-1 value and display it.
    */
   for(i = 0; i < argc; i++)
   {
      /*
       *  We start the counter at 0 to guarantee entry into the for
       *  loop. So if 'i' is zero, we will increment it now.  If there
       *  is no argv[1], we will use STDIN below.
       */
      if (i == 0)
         i++;

      if (argc == 1 || string_is_equal(argv[i],"-"))
      {
#ifdef WIN32
         setmode(fileno(stdin), _O_BINARY);
#endif
         fp = stdin;
         reading_stdin = 1;
      }
      else
      {
         if (!(fp = fopen(argv[i],"rb")))
         {
            fprintf(stderr,
                  "sha: unable to open file %s\n",
                  argv[i]);
            return 2;
         }
         reading_stdin = 0;
      }

      /*
       *  We do not want to read STDIN multiple times
       */
      if (reading_stdin)
      {
         if (read_stdin)
            continue;

         read_stdin = 1;
      }

      /*
       *  Reset the SHA-1 context and process input
       */
      SHA1Reset(&sha);

      c = fgetc(fp);
      while(!feof(fp))
      {
         SHA1Input(&sha, &c, 1);
         c = fgetc(fp);
      }

      if (!reading_stdin)
         fclose(fp);

      if (!SHA1Result(&sha))
      {
         fprintf(stderr,
               "sha: could not compute message digest for %s\n",
               reading_stdin?"STDIN":argv[i]);
      }
      else
      {
         printf( "%08X %08X %08X %08X %08X - %s\n",
               sha.Message_Digest[0],
               sha.Message_Digest[1],
               sha.Message_Digest[2],
               sha.Message_Digest[3],
               sha.Message_Digest[4],
               reading_stdin?"STDIN":argv[i]);
      }
   }

   return 0;
}