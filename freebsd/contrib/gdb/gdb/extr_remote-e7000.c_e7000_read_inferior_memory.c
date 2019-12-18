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
 int /*<<< orphan*/  expect_full_prompt () ; 
 int /*<<< orphan*/  expect_prompt () ; 
 int gbyte () ; 
 int gch () ; 
 char* paddr_nz (int) ; 
 int /*<<< orphan*/  puts_e7000debug (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static int
e7000_read_inferior_memory (CORE_ADDR memaddr, unsigned char *myaddr, int len)
{
  int count;
  int c;
  int i;
  char buf[200];
  /* Starting address of this pass.  */

/*  printf("READ INF %x %x %d\n", memaddr, myaddr, len); */
  if (((memaddr - 1) + len) < memaddr)
    {
      errno = EIO;
      return 0;
    }

  sprintf (buf, "m %s;l\r", paddr_nz (memaddr));
  puts_e7000debug (buf);

  for (count = 0; count < len; count += 4)
    {
      /* Suck away the address */
      c = gch ();
      while (c != ' ')
	c = gch ();
      c = gch ();
      if (c == '*')
	{			/* Some kind of error */
	  puts_e7000debug (".\r");	/* Some errors leave us in memory input mode */
	  expect_full_prompt ();
	  return -1;
	}
      while (c != ' ')
	c = gch ();

      /* Now read in the data */
      for (i = 0; i < 4; i++)
	{
	  int b = gbyte ();
	  if (count + i < len)
	    {
	      myaddr[count + i] = b;
	    }
	}

      /* Skip the trailing ? and send a . to end and a cr for more */
      gch ();
      gch ();
      if (count + 4 >= len)
	puts_e7000debug (".\r");
      else
	puts_e7000debug ("\r");

    }
  expect_prompt ();
  return len;
}