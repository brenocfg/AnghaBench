#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* ptr; } ;
typedef  TYPE_1__ sstring ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  MAKE_SSTRING_SPACE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SSTRING_PUT (TYPE_1__*,int) ; 
 int getc (int /*<<< orphan*/ *) ; 

int
scan_string (FILE *fp, sstring *s, int init)
{
  int c;

  for (;;)
    {
      c = getc (fp);
      if (c == EOF || c == '\n')
	break;
      if (c == init)
	{
	  c = getc (fp);
	  break;
	}
      if (c == '\\')
	{
	  c = getc (fp);
	  if (c == EOF)
	    break;
	  if (c == '\n')
	    continue;
	}
      SSTRING_PUT (s, c);
    }
  MAKE_SSTRING_SPACE (s, 1);
  *s->ptr = 0;
  return c;
}