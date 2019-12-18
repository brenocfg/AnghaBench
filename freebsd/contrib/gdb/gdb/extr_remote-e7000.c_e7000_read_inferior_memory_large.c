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
 int gch () ; 
 unsigned char get_hex (int*) ; 
 char* paddr_nz (int) ; 
 int /*<<< orphan*/  puts_e7000debug (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static int
e7000_read_inferior_memory_large (CORE_ADDR memaddr, unsigned char *myaddr,
				  int len)
{
  int count;
  int c;
  char buf[200];

  /* Starting address of this pass.  */

  if (((memaddr - 1) + len) < memaddr)
    {
      errno = EIO;
      return 0;
    }

  sprintf (buf, "d %s %s\r", paddr_nz (memaddr), paddr_nz (memaddr + len - 1));
  puts_e7000debug (buf);

  count = 0;
  c = gch ();

  /* skip down to the first ">" */
  while (c != '>')
    c = gch ();
  /* now skip to the end of that line */
  while (c != '\r')
    c = gch ();
  c = gch ();

  while (count < len)
    {
      /* get rid of any white space before the address */
      while (c <= ' ')
	c = gch ();

      /* Skip the address */
      get_hex (&c);

      /* read in the bytes on the line */
      while (c != '"' && count < len)
	{
	  if (c == ' ')
	    c = gch ();
	  else
	    {
	      myaddr[count++] = get_hex (&c);
	    }
	}
      /* throw out the rest of the line */
      while (c != '\r')
	c = gch ();
    }

  /* wait for the ":" prompt */
  while (c != ':')
    c = gch ();

  return len;
}