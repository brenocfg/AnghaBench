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
struct mem_region {scalar_t__ enabled_p; struct mem_region* next; } ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  dcache_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  mem_disable (int) ; 
 struct mem_region* mem_region_chain ; 
 int /*<<< orphan*/  target_dcache ; 

__attribute__((used)) static void
mem_disable_command (char *args, int from_tty)
{
  char *p = args;
  char *p1;
  int num;
  struct mem_region *m;

  dcache_invalidate (target_dcache);

  if (p == 0)
    {
      for (m = mem_region_chain; m; m = m->next)
	m->enabled_p = 0;
    }
  else
    while (*p)
      {
	p1 = p;
	while (*p1 >= '0' && *p1 <= '9')
	  p1++;
	if (*p1 && *p1 != ' ' && *p1 != '\t')
	  error ("Arguments must be memory region numbers.");

	num = atoi (p);
	mem_disable (num);

	p = p1;
	while (*p == ' ' || *p == '\t')
	  p++;
      }
}