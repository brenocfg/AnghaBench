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
struct list {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  ar_directory_doer ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  map_over_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct list*) ; 
 int /*<<< orphan*/ * open_inarch (char*,char*) ; 
 scalar_t__ outfile ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stdout ; 

void
ar_directory (char *ar_name, struct list *list, char *output)
{
  bfd *arch;

  arch = open_inarch (ar_name, (char *) NULL);
  if (output)
    {
      outfile = fopen(output,"w");
      if (outfile == 0)
	{
	  outfile = stdout;
	  fprintf (stderr,_("Can't open file %s\n"), output);
	  output = 0;
	}
    }
  else
    outfile = stdout;

  map_over_list (arch, ar_directory_doer, list);

  bfd_close (arch);

  if (output)
   fclose (outfile);
}