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
struct display {scalar_t__ enabled_p; struct display* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  disable_display (int /*<<< orphan*/ ) ; 
 struct display* display_chain ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static void
disable_display_command (char *args, int from_tty)
{
  char *p = args;
  char *p1;
  struct display *d;

  if (p == 0)
    {
      for (d = display_chain; d; d = d->next)
	d->enabled_p = 0;
    }
  else
    while (*p)
      {
	p1 = p;
	while (*p1 >= '0' && *p1 <= '9')
	  p1++;
	if (*p1 && *p1 != ' ' && *p1 != '\t')
	  error ("Arguments must be display numbers.");

	disable_display (atoi (p));

	p = p1;
	while (*p == ' ' || *p == '\t')
	  p++;
      }
}