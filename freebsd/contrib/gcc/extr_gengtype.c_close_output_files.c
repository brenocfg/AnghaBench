#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* outf_p ;
struct TYPE_3__ {size_t bufused; scalar_t__* buf; int /*<<< orphan*/  name; struct TYPE_3__* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fwrite (scalar_t__*,int,size_t,int /*<<< orphan*/ *) ; 
 TYPE_1__* output_files ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void
close_output_files (void)
{
  outf_p of;

  for (of = output_files; of; of = of->next)
    {
      FILE * newfile;

      newfile = fopen (of->name, "r");
      if (newfile != NULL )
	{
	  int no_write_p;
	  size_t i;

	  for (i = 0; i < of->bufused; i++)
	    {
	      int ch;
	      ch = fgetc (newfile);
	      if (ch == EOF || ch != (unsigned char) of->buf[i])
		break;
	    }
	  no_write_p = i == of->bufused && fgetc (newfile) == EOF;
	  fclose (newfile);

	  if (no_write_p)
	    continue;
	}

      newfile = fopen (of->name, "w");
      if (newfile == NULL)
	{
	  perror ("opening output file");
	  exit (1);
	}
      if (fwrite (of->buf, 1, of->bufused, newfile) != of->bufused)
	{
	  perror ("writing output file");
	  exit (1);
	}
      if (fclose (newfile) != 0)
	{
	  perror ("closing output file");
	  exit (1);
	}
    }
}