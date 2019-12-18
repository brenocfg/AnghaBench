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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  format_list ;
typedef  int /*<<< orphan*/  Image ;

/* Variables and functions */
 int NO_RESEED ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeimage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initimage (int /*<<< orphan*/ *,int,char const*,int) ; 
 int /*<<< orphan*/  newimage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_opts (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_one_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reseed () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int testimage (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
test_one_file(const char *file_name, format_list *formats, png_uint_32 opts,
   int stride_extra, int log_pass)
{
   int result;
   Image image;

   if (!(opts & NO_RESEED))
      reseed(); /* ensure that the random numbers don't depend on file order */
   newimage(&image);
   initimage(&image, opts, file_name, stride_extra);
   result = read_one_file(&image);
   if (result)
      result = testimage(&image, opts, formats);
   freeimage(&image);

   /* Ensure that stderr is flushed into any log file */
   fflush(stderr);

   if (log_pass)
   {
      if (result)
         printf("PASS:");

      else
         printf("FAIL:");

#     ifndef PNG_SIMPLIFIED_WRITE_SUPPORTED
         printf(" (no write)");
#     endif

      print_opts(opts);
      printf(" %s\n", file_name);
      /* stdout may not be line-buffered if it is piped to a file, so: */
      fflush(stdout);
   }

   else if (!result)
      exit(1);

   return result;
}