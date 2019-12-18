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
 int /*<<< orphan*/  fputc_unfiltered (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ isascii (int) ; 

__attribute__((used)) static int
mywrite (void *arg, char const *buffer, int len)
{
  int i;
  char *e;

  e = (char *) buffer;
  for (i = 0; i < len; i++)
    {
      if (isascii ((int) *e))
	{
	  fputc_unfiltered ((int) *e, gdb_stdout);
	  e++;
	}
    }

  return len;
}