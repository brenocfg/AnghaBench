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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(FILE *fp)
{
   if (fp != NULL) fclose(fp);

   fprintf(stderr,
"Usage:\n"
" timepng --assemble <assembly> {files}\n"
"  Read the files into <assembly>, output the count.  Options are ignored.\n"
" timepng --dissemble <assembly> <count> [options]\n"
"  Time <count> files from <assembly>, additional files may not be given.\n"
" Otherwise:\n"
"  Read the files into a temporary file and time the decode\n"
"Transforms:\n"
"  --by-image: read by image with png_read_png\n"
"  --<transform>: implies by-image, use PNG_TRANSFORM_<transform>\n"
"  Otherwise: read by row using png_read_row (to a single row buffer)\n"
   /* ISO C90 string length max 509 */);fprintf(stderr,
"{files}:\n"
"  PNG files to copy into the assembly and time.  Invalid files are skipped\n"
"  with appropriate error messages.  If no files are given the list of files\n"
"  is read from stdin with each file name terminated by a newline\n"
"Output:\n"
"  For --assemble the output is the name of the assembly file followed by the\n"
"  count of the files it contains; the arguments for --dissemble.  Otherwise\n"
"  the output is the total decode time in seconds.\n");

   exit(99);
}