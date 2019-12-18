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
 char* P_tmpdir ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getpid () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int,int /*<<< orphan*/ ) ; 
 char* tmpnam_buffer ; 
 int /*<<< orphan*/  tmpnam_counter ; 

char *
tmpnam (char *s)
{
  int pid = getpid ();

  if (s == NULL)
    s = tmpnam_buffer;

  /*  Generate the filename and make sure that there isn't one called
      it already.  */

  while (1)
    {
      FILE *f;
      sprintf (s, "%s/%s%x.%x", P_tmpdir, "t", pid, tmpnam_counter);
      f = fopen (s, "r");
      if (f == NULL)
	break;
      tmpnam_counter++;
      fclose (f);
    }

  return s;
}