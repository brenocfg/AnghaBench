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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  expect (char*,int) ; 
 int /*<<< orphan*/  expect_prompt (int) ; 
 int /*<<< orphan*/  get_hex_byte (char*) ; 
 int /*<<< orphan*/  printf_stdebug (char*,unsigned long,int) ; 

__attribute__((used)) static int
st2000_read_inferior_memory (CORE_ADDR memaddr, char *myaddr, int len)
{
  int i;

  /* Number of bytes read so far.  */
  int count;

  /* Starting address of this pass.  */
  unsigned long startaddr;

  /* Number of bytes to read in this pass.  */
  int len_this_pass;

  /* Note that this code works correctly if startaddr is just less
     than UINT_MAX (well, really CORE_ADDR_MAX if there was such a
     thing).  That is, something like
     st2000_read_bytes (CORE_ADDR_MAX - 4, foo, 4)
     works--it never adds len to memaddr and gets 0.  */
  /* However, something like
     st2000_read_bytes (CORE_ADDR_MAX - 3, foo, 4)
     doesn't need to work.  Detect it and give up if there's an attempt
     to do that.  */
  if (((memaddr - 1) + len) < memaddr)
    {
      errno = EIO;
      return 0;
    }

  startaddr = memaddr;
  count = 0;
  while (count < len)
    {
      len_this_pass = 16;
      if ((startaddr % 16) != 0)
	len_this_pass -= startaddr % 16;
      if (len_this_pass > (len - count))
	len_this_pass = (len - count);

      printf_stdebug ("DI.L %x %x\r", startaddr, len_this_pass);
      expect (":  ", 1);

      for (i = 0; i < len_this_pass; i++)
	get_hex_byte (&myaddr[count++]);

      expect_prompt (1);

      startaddr += len_this_pass;
    }
  return len;
}