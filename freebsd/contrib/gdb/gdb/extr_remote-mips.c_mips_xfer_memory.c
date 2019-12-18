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
struct target_ops {int dummy; } ;
struct mem_attrib {int dummy; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
 char* alloca (int) ; 
 int errno ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ mask_address_p ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mips_fetch_word (int) ; 
 int mips_store_word (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write,
		  struct mem_attrib *attrib, struct target_ops *target)
{
  int i;
  CORE_ADDR addr;
  int count;
  char *buffer;
  int status;

  /* PMON targets do not cope well with 64 bit addresses.  Mask the
     value down to 32 bits. */
  if (mask_address_p)
    memaddr &= (CORE_ADDR) 0xffffffff;

  /* Round starting address down to longword boundary.  */
  addr = memaddr & ~3;
  /* Round ending address up; get number of longwords that makes.  */
  count = (((memaddr + len) - addr) + 3) / 4;
  /* Allocate buffer of that many longwords.  */
  buffer = alloca (count * 4);

  if (write)
    {
      /* Fill start and end extra bytes of buffer with existing data.  */
      if (addr != memaddr || len < 4)
	{
	  /* Need part of initial word -- fetch it.  */
	  store_unsigned_integer (&buffer[0], 4, mips_fetch_word (addr));
	}

      if (count > 1)
	{
	  /* Need part of last word -- fetch it.  FIXME: we do this even
	     if we don't need it.  */
	  store_unsigned_integer (&buffer[(count - 1) * 4], 4,
				  mips_fetch_word (addr + (count - 1) * 4));
	}

      /* Copy data to be written over corresponding part of buffer */

      memcpy ((char *) buffer + (memaddr & 3), myaddr, len);

      /* Write the entire buffer.  */

      for (i = 0; i < count; i++, addr += 4)
	{
	  status = mips_store_word (addr,
			       extract_unsigned_integer (&buffer[i * 4], 4),
				    NULL);
	  /* Report each kilobyte (we download 32-bit words at a time) */
	  if (i % 256 == 255)
	    {
	      printf_unfiltered ("*");
	      gdb_flush (gdb_stdout);
	    }
	  if (status)
	    {
	      errno = status;
	      return 0;
	    }
	  /* FIXME: Do we want a QUIT here?  */
	}
      if (count >= 256)
	printf_unfiltered ("\n");
    }
  else
    {
      /* Read all the longwords */
      for (i = 0; i < count; i++, addr += 4)
	{
	  store_unsigned_integer (&buffer[i * 4], 4, mips_fetch_word (addr));
	  QUIT;
	}

      /* Copy appropriate bytes out of the buffer.  */
      memcpy (myaddr, buffer + (memaddr & 3), len);
    }
  return len;
}