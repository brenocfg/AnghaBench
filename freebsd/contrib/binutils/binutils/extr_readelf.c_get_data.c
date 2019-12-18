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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _ (char*) ; 
 unsigned long archive_file_offset ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,unsigned long,char const*) ; 
 size_t fread (void*,size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 void* malloc (size_t) ; 

__attribute__((used)) static void *
get_data (void *var, FILE *file, long offset, size_t size, size_t nmemb,
	  const char *reason)
{
  void *mvar;

  if (size == 0 || nmemb == 0)
    return NULL;

  if (fseek (file, archive_file_offset + offset, SEEK_SET))
    {
      error (_("Unable to seek to 0x%lx for %s\n"),
	     archive_file_offset + offset, reason);
      return NULL;
    }

  mvar = var;
  if (mvar == NULL)
    {
      /* Check for overflow.  */
      if (nmemb < (~(size_t) 0 - 1) / size)
	/* + 1 so that we can '\0' terminate invalid string table sections.  */
	mvar = malloc (size * nmemb + 1);

      if (mvar == NULL)
	{
	  error (_("Out of memory allocating 0x%lx bytes for %s\n"),
		 (unsigned long)(size * nmemb), reason);
	  return NULL;
	}

      ((char *) mvar)[size * nmemb] = '\0';
    }

  if (fread (mvar, size, nmemb, file) != nmemb)
    {
      error (_("Unable to read in 0x%lx bytes of %s\n"),
	     (unsigned long)(size * nmemb), reason);
      if (mvar != var)
	free (mvar);
      return NULL;
    }

  return mvar;
}