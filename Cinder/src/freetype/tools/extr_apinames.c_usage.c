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

/* Variables and functions */
 int /*<<< orphan*/  PROGRAM_NAME ; 
 int /*<<< orphan*/  PROGRAM_VERSION ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage( void )
{
  static const char* const  format =
   "%s %s: extract FreeType API names from header files\n\n"
   "this program is used to extract the list of public FreeType API\n"
   "functions. It receives the list of header files as argument and\n"
   "generates a sorted list of unique identifiers\n\n"

   "usage: %s header1 [options] [header2 ...]\n\n"

   "options:   -      : parse the content of stdin, ignore arguments\n"
   "           -v     : verbose mode, output sent to standard error\n"
   "           -oFILE : write output to FILE instead of standard output\n"
   "           -dNAME : indicate DLL file name, 'freetype.dll' by default\n"
   "           -w     : output .DEF file for Visual C++ and Mingw\n"
   "           -wB    : output .DEF file for Borland C++\n"
   "           -wW    : output Watcom Linker Response File\n"
   "           -wN    : output NetWare Import File\n"
   "           -wL    : output version map for GNU or Solaris linker\n"
   "\n";

  fprintf( stderr,
           format,
           PROGRAM_NAME,
           PROGRAM_VERSION,
           PROGRAM_NAME
           );
  exit(1);
}