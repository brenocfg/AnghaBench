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
 char* REPORT_BUGS_TO ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  list_supported_targets (char*,int /*<<< orphan*/ *) ; 
 char* program_name ; 

__attribute__((used)) static void
usage (FILE *stream, int status)
{
  fprintf (stream, _("Usage: %s [option(s)] [input-file]\n"),
	   program_name);
  fprintf (stream, _(" The options are:\n\
  -a --ascii_in                Read input file as ASCII file\n\
  -A --ascii_out               Write binary messages as ASCII\n\
  -b --binprefix               .bin filename is prefixed by .mc filename_ for uniqueness.\n\
  -c --customflag              Set custom flags for messages\n\
  -C --codepage_in=<val>       Set codepage when reading mc text file\n\
  -d --decimal_values          Print values to text files decimal\n\
  -e --extension=<extension>   Set header extension used on export header file\n\
  -F --target <target>         Specify output target for endianess.\n\
  -h --headerdir=<directory>   Set the export directory for headers\n\
  -u --unicode_in              Read input file as UTF16 file\n\
  -U --unicode_out             Write binary messages as UFT16\n\
  -m --maxlength=<val>         Set the maximal allowed message length\n\
  -n --nullterminate           Automatic add a zero termination to strings\n\
  -o --hresult_use             Use HRESULT definition instead of status code definition\n\
  -O --codepage_out=<val>      Set codepage used for writing text file\n\
  -r --rcdir=<directory>       Set the export directory for rc files\n\
  -x --xdbg=<directory>        Where to create the .dbg C include file\n\
                               that maps message ID's to their symbolic name.\n\
"));
  fprintf (stream, _("\
  -H --help                    Print this help message\n\
  -v --verbose                 Verbose - tells you what it's doing\n\
  -V --version                 Print version information\n"));

  list_supported_targets (program_name, stream);

  if (REPORT_BUGS_TO[0] && status == 0)
    fprintf (stream, _("Report bugs to %s\n"), REPORT_BUGS_TO);

  exit (status);
}