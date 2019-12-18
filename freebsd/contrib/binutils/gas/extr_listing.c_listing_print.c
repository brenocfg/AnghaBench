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
 scalar_t__ EOF ; 
 int /*<<< orphan*/  FOPEN_WT ; 
 int LISTING_LISTING ; 
 int LISTING_NOFORM ; 
 int LISTING_SYMBOLS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * last_open_file ; 
 int /*<<< orphan*/ * list_file ; 
 int /*<<< orphan*/  list_symbol_table () ; 
 int listing ; 
 int /*<<< orphan*/  listing_listing (char*) ; 
 scalar_t__ paper_height ; 
 int /*<<< orphan*/ * stdout ; 
 char* subtitle ; 
 char* title ; 
 int /*<<< orphan*/  xstrerror (int /*<<< orphan*/ ) ; 

void
listing_print (char *name)
{
  int using_stdout;

  title = "";
  subtitle = "";

  if (name == NULL)
    {
      list_file = stdout;
      using_stdout = 1;
    }
  else
    {
      list_file = fopen (name, FOPEN_WT);
      if (list_file != NULL)
	using_stdout = 0;
      else
	{
	  as_warn (_("can't open %s: %s"), name, xstrerror (errno));
	  list_file = stdout;
	  using_stdout = 1;
	}
    }

  if (listing & LISTING_NOFORM)
    paper_height = 0;

  if (listing & LISTING_LISTING)
    listing_listing (name);

  if (listing & LISTING_SYMBOLS)
    list_symbol_table ();

  if (! using_stdout)
    {
      if (fclose (list_file) == EOF)
	as_warn (_("can't close %s: %s"), name, xstrerror (errno));
    }

  if (last_open_file)
    fclose (last_open_file);
}