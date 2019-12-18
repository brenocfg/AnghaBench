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
 int /*<<< orphan*/ * encoding ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  gdb_stderr ; 

__attribute__((used)) static int
pmon_makeb64 (unsigned long v, char *p, int n, int *chksum)
{
  int count = (n / 6);

  if ((n % 12) != 0)
    {
      fprintf_unfiltered (gdb_stderr,
			  "Fast encoding bitcount must be a multiple of 12bits: %dbit%s\n", n, (n == 1) ? "" : "s");
      return (0);
    }
  if (n > 36)
    {
      fprintf_unfiltered (gdb_stderr,
			  "Fast encoding cannot process more than 36bits at the moment: %dbits\n", n);
      return (0);
    }

  /* Deal with the checksum: */
  if (chksum != NULL)
    {
      switch (n)
	{
	case 36:
	  *chksum += ((v >> 24) & 0xFFF);
	case 24:
	  *chksum += ((v >> 12) & 0xFFF);
	case 12:
	  *chksum += ((v >> 0) & 0xFFF);
	}
    }

  do
    {
      n -= 6;
      *p++ = encoding[(v >> n) & 0x3F];
    }
  while (n > 0);

  return (count);
}