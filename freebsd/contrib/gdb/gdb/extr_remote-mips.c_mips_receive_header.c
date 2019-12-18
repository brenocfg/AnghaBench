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
 int /*<<< orphan*/  HDR_CHECK (int) ; 
 int HDR_LENGTH ; 
 int SERIAL_TIMEOUT ; 
 int SYN ; 
 int /*<<< orphan*/  fputc_readable (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc_unfiltered (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdtarg ; 
 scalar_t__ isprint (int) ; 
 scalar_t__ isspace (int) ; 
 int /*<<< orphan*/  mips_error (char*,int) ; 
 int /*<<< orphan*/  mips_initializing ; 
 int mips_readchar (int) ; 
 int mips_syn_garbage ; 
 scalar_t__ remote_debug ; 

__attribute__((used)) static int
mips_receive_header (unsigned char *hdr, int *pgarbage, int ch, int timeout)
{
  int i;

  while (1)
    {
      /* Wait for a SYN.  mips_syn_garbage is intended to prevent
         sitting here indefinitely if the board sends us one garbage
         character per second.  ch may already have a value from the
         last time through the loop.  */
      while (ch != SYN)
	{
	  ch = mips_readchar (timeout);
	  if (ch == SERIAL_TIMEOUT)
	    return -1;
	  if (ch != SYN)
	    {
	      /* Printing the character here lets the user of gdb see
	         what the program is outputting, if the debugging is
	         being done on the console port.  Don't use _filtered:
	         we can't deal with a QUIT out of target_wait and
	         buffered target output confuses the user. */
 	      if (!mips_initializing || remote_debug > 0)
  		{
		  if (isprint (ch) || isspace (ch))
		    {
		      fputc_unfiltered (ch, gdb_stdtarg);
		    }
		  else
		    {
		      fputc_readable (ch, gdb_stdtarg);
		    }
		  gdb_flush (gdb_stdtarg);
  		}
	      
	      /* Only count unprintable characters. */
	      if (! (isprint (ch) || isspace (ch)))
		(*pgarbage) += 1;

	      if (mips_syn_garbage > 0
		  && *pgarbage > mips_syn_garbage)
		mips_error ("Debug protocol failure:  more than %d characters before a sync.",
			    mips_syn_garbage);
	    }
	}

      /* Get the packet header following the SYN.  */
      for (i = 1; i < HDR_LENGTH; i++)
	{
	  ch = mips_readchar (timeout);
	  if (ch == SERIAL_TIMEOUT)
	    return -1;
	  /* Make sure this is a header byte.  */
	  if (ch == SYN || !HDR_CHECK (ch))
	    break;

	  hdr[i] = ch;
	}

      /* If we got the complete header, we can return.  Otherwise we
         loop around and keep looking for SYN.  */
      if (i >= HDR_LENGTH)
	return 0;
    }
}