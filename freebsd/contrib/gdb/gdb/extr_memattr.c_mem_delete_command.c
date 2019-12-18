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
 int atoi (char*) ; 
 int /*<<< orphan*/  dcache_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  mem_clear () ; 
 int /*<<< orphan*/  mem_delete (int) ; 
 scalar_t__ query (char*) ; 
 int /*<<< orphan*/  target_dcache ; 

__attribute__((used)) static void
mem_delete_command (char *args, int from_tty)
{
  char *p = args;
  char *p1;
  int num;

  dcache_invalidate (target_dcache);

  if (p == 0)
    {
      if (query ("Delete all memory regions? "))
	mem_clear ();
      dont_repeat ();
      return;
    }

  while (*p)
    {
      p1 = p;
      while (*p1 >= '0' && *p1 <= '9')
	p1++;
      if (*p1 && *p1 != ' ' && *p1 != '\t')
	error ("Arguments must be memory region numbers.");

      num = atoi (p);
      mem_delete (num);

      p = p1;
      while (*p == ' ' || *p == '\t')
	p++;
    }

  dont_repeat ();
}