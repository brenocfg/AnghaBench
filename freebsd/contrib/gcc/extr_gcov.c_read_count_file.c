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
struct function_info {unsigned int ident; unsigned int checksum; unsigned int num_counts; int /*<<< orphan*/ * counts; int /*<<< orphan*/  name; struct function_info* next; } ;
typedef  struct function_info function_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCOV_COUNTER_ARCS ; 
 int /*<<< orphan*/  GCOV_DATA_MAGIC ; 
 unsigned int GCOV_TAG_COUNTER_LENGTH (unsigned int) ; 
 unsigned int GCOV_TAG_FOR_COUNTER (int /*<<< orphan*/ ) ; 
 unsigned int GCOV_TAG_FUNCTION ; 
 unsigned int GCOV_TAG_OBJECT_SUMMARY ; 
 unsigned int GCOV_TAG_PROGRAM_SUMMARY ; 
 int /*<<< orphan*/  GCOV_UNSIGNED2STRING (char*,unsigned int) ; 
 unsigned int GCOV_VERSION ; 
 int /*<<< orphan*/ * XCNEWVEC (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int bbg_stamp ; 
 int /*<<< orphan*/  da_file_name ; 
 int /*<<< orphan*/  fnotice (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct function_info* functions ; 
 int /*<<< orphan*/  gcov_close () ; 
 int gcov_is_error () ; 
 int /*<<< orphan*/  gcov_magic (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_open (int /*<<< orphan*/ ,int) ; 
 unsigned long gcov_position () ; 
 scalar_t__ gcov_read_counter () ; 
 int /*<<< orphan*/  gcov_read_summary (int /*<<< orphan*/ *) ; 
 unsigned int gcov_read_unsigned () ; 
 int /*<<< orphan*/  gcov_sync (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  gcov_type ; 
 int no_data_file ; 
 int /*<<< orphan*/  object_summary ; 
 int /*<<< orphan*/  program_count ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
read_count_file (void)
{
  unsigned ix;
  unsigned version;
  unsigned tag;
  function_t *fn = NULL;
  int error = 0;

  if (!gcov_open (da_file_name, 1))
    {
      fnotice (stderr, "%s:cannot open data file, assuming not executed\n",
	       da_file_name);
      no_data_file = 1;
      return 0;
    }
  if (!gcov_magic (gcov_read_unsigned (), GCOV_DATA_MAGIC))
    {
      fnotice (stderr, "%s:not a gcov data file\n", da_file_name);
    cleanup:;
      gcov_close ();
      return 1;
    }
  version = gcov_read_unsigned ();
  if (version != GCOV_VERSION)
    {
      char v[4], e[4];

      GCOV_UNSIGNED2STRING (v, version);
      GCOV_UNSIGNED2STRING (e, GCOV_VERSION);
      
      fnotice (stderr, "%s:version '%.4s', prefer version '%.4s'\n",
	       da_file_name, v, e);
    }
  tag = gcov_read_unsigned ();
  if (tag != bbg_stamp)
    {
      fnotice (stderr, "%s:stamp mismatch with graph file\n", da_file_name);
      goto cleanup;
    }

  while ((tag = gcov_read_unsigned ()))
    {
      unsigned length = gcov_read_unsigned ();
      unsigned long base = gcov_position ();

      if (tag == GCOV_TAG_OBJECT_SUMMARY)
	gcov_read_summary (&object_summary);
      else if (tag == GCOV_TAG_PROGRAM_SUMMARY)
	program_count++;
      else if (tag == GCOV_TAG_FUNCTION)
	{
	  unsigned ident = gcov_read_unsigned ();
	  struct function_info *fn_n = functions;

	  for (fn = fn ? fn->next : NULL; ; fn = fn->next)
	    {
	      if (fn)
		;
	      else if ((fn = fn_n))
		fn_n = NULL;
	      else
		{
		  fnotice (stderr, "%s:unknown function '%u'\n",
			   da_file_name, ident);
		  break;
		}
	      if (fn->ident == ident)
		break;
	    }

	  if (!fn)
	    ;
	  else if (gcov_read_unsigned () != fn->checksum)
	    {
	    mismatch:;
	      fnotice (stderr, "%s:profile mismatch for '%s'\n",
		       da_file_name, fn->name);
	      goto cleanup;
	    }
	}
      else if (tag == GCOV_TAG_FOR_COUNTER (GCOV_COUNTER_ARCS) && fn)
	{
	  if (length != GCOV_TAG_COUNTER_LENGTH (fn->num_counts))
	    goto mismatch;

	  if (!fn->counts)
	    fn->counts = XCNEWVEC (gcov_type, fn->num_counts);

	  for (ix = 0; ix != fn->num_counts; ix++)
	    fn->counts[ix] += gcov_read_counter ();
	}
      gcov_sync (base, length);
      if ((error = gcov_is_error ()))
	{
	  fnotice (stderr, error < 0 ? "%s:overflowed\n" : "%s:corrupted\n",
		   da_file_name);
	  goto cleanup;
	}
    }

  gcov_close ();
  return 0;
}