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
 scalar_t__ ISDIGIT (char const) ; 
 scalar_t__ ISLOWER (char const) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  printf (char*,char const) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
print_path (const char *path)
{
  int len = strlen (path);
  int i;

  if (len == 0)
    {
      /* Don't emit "pat", since we may try to take the address of it,
	 which isn't what is intended.  */
      fputs ("PATTERN (insn)", stdout);
      return;
    }

  /* We first write out the operations (XEXP or XVECEXP) in reverse
     order, then write "pat", then the indices in forward order.  */

  for (i = len - 1; i >= 0 ; i--)
    {
      if (ISLOWER (path[i]))
	fputs ("XVECEXP (", stdout);
      else if (ISDIGIT (path[i]))
	fputs ("XEXP (", stdout);
      else
	gcc_unreachable ();
    }

  fputs ("pat", stdout);

  for (i = 0; i < len; i++)
    {
      if (ISLOWER (path[i]))
	printf (", 0, %d)", path[i] - 'a');
      else if (ISDIGIT(path[i]))
	printf (", %d)", path[i] - '0');
      else
	gcc_unreachable ();
    }
}