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
 int DEPRECATED_REGISTER_BYTE (int) ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  deprecated_read_register_gen (int,char*) ; 
 int /*<<< orphan*/ * deprecated_registers ; 
 int /*<<< orphan*/  deprecated_write_register_gen (int,char*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  target_prepare_to_store () ; 
 int /*<<< orphan*/  target_store_registers (int) ; 

void
deprecated_write_register_bytes (int myregstart, char *myaddr, int inlen)
{
  int myregend = myregstart + inlen;
  int regnum;

  target_prepare_to_store ();

  /* Scan through the registers updating any that are covered by the
     range myregstart<=>myregend using write_register_gen, which does
     nice things like handling threads, and avoiding updates when the
     new and old contents are the same.  */

  for (regnum = 0; regnum < NUM_REGS + NUM_PSEUDO_REGS; regnum++)
    {
      int regstart, regend;

      regstart = DEPRECATED_REGISTER_BYTE (regnum);
      regend = regstart + DEPRECATED_REGISTER_RAW_SIZE (regnum);

      /* Is this register completely outside the range the user is writing?  */
      if (myregend <= regstart || regend <= myregstart)
	/* do nothing */ ;		

      /* Is this register completely within the range the user is writing?  */
      else if (myregstart <= regstart && regend <= myregend)
	deprecated_write_register_gen (regnum, myaddr + (regstart - myregstart));

      /* The register partially overlaps the range being written.  */
      else
	{
	  char regbuf[MAX_REGISTER_SIZE];
	  /* What's the overlap between this register's bytes and
             those the caller wants to write?  */
	  int overlapstart = max (regstart, myregstart);
	  int overlapend   = min (regend,   myregend);

	  /* We may be doing a partial update of an invalid register.
	     Update it from the target before scribbling on it.  */
	  deprecated_read_register_gen (regnum, regbuf);

	  memcpy (&deprecated_registers[overlapstart],
		  myaddr + (overlapstart - myregstart),
		  overlapend - overlapstart);

	  target_store_registers (regnum);
	}
    }
}