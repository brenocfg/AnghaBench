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
struct d_growable_string {int allocation_failure; int alc; char* buf; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ realloc (char*,size_t) ; 

__attribute__((used)) static inline void
d_growable_string_resize (struct d_growable_string *dgs, size_t need)
{
  size_t newalc;
  char *newbuf;

  if (dgs->allocation_failure)
    return;

  /* Start allocation at two bytes to avoid any possibility of confusion
     with the special value of 1 used as a return in *palc to indicate
     allocation failures.  */
  newalc = dgs->alc > 0 ? dgs->alc : 2;
  while (newalc < need)
    newalc <<= 1;

  newbuf = (char *) realloc (dgs->buf, newalc);
  if (newbuf == NULL)
    {
      free (dgs->buf);
      dgs->buf = NULL;
      dgs->len = 0;
      dgs->alc = 0;
      dgs->allocation_failure = 1;
      return;
    }
  dgs->buf = newbuf;
  dgs->alc = newalc;
}