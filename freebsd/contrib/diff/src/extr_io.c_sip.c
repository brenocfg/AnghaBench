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
typedef  int /*<<< orphan*/  word ;
struct file_data {scalar_t__ desc; int bufsize; int eof; scalar_t__ buffered; void* buffer; int /*<<< orphan*/  name; int /*<<< orphan*/  stat; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ PTRDIFF_MAX ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  STAT_BLOCKSIZE (int /*<<< orphan*/ ) ; 
 int binary_file_p (void*,scalar_t__) ; 
 int buffer_lcm (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  file_block_read (struct file_data*,int) ; 
 int lseek (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfatal_with_name (int /*<<< orphan*/ ) ; 
 int set_binary_mode (scalar_t__,int) ; 
 void* xmalloc (int) ; 

__attribute__((used)) static bool
sip (struct file_data *current, bool skip_test)
{
  /* If we have a nonexistent file at this stage, treat it as empty.  */
  if (current->desc < 0)
    {
      /* Leave room for a sentinel.  */
      current->bufsize = sizeof (word);
      current->buffer = xmalloc (current->bufsize);
    }
  else
    {
      current->bufsize = buffer_lcm (sizeof (word),
				     STAT_BLOCKSIZE (current->stat),
				     PTRDIFF_MAX - 2 * sizeof (word));
      current->buffer = xmalloc (current->bufsize);

      if (! skip_test)
	{
	  /* Check first part of file to see if it's a binary file.  */

	  bool was_binary = set_binary_mode (current->desc, true);
	  off_t buffered;
	  file_block_read (current, current->bufsize);
	  buffered = current->buffered;

	  if (! was_binary)
	    {
	      /* Revert to text mode and seek back to the beginning to
		 reread the file.  Use relative seek, since file
		 descriptors like stdin might not start at offset
		 zero.  */

	      if (lseek (current->desc, - buffered, SEEK_CUR) == -1)
		pfatal_with_name (current->name);
	      set_binary_mode (current->desc, false);
	      current->buffered = 0;
	      current->eof = false;
	    }

	  return binary_file_p (current->buffer, buffered);
	}
    }

  current->buffered = 0;
  current->eof = false;
  return false;
}