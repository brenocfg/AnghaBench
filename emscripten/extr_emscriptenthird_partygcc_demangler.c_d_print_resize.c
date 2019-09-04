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
struct d_print_info {char* buf; size_t len; size_t alc; int allocation_failure; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ realloc (char*,size_t) ; 

__attribute__((used)) static void
d_print_resize (struct d_print_info *dpi, size_t add)
{
  size_t need;

  if (dpi->buf == NULL)
    return;
  need = dpi->len + add;
  while (need > dpi->alc)
    {
      size_t newalc;
      char *newbuf;

      newalc = dpi->alc * 2;
      newbuf = (char *) realloc (dpi->buf, newalc);
      if (newbuf == NULL)
	{
	  free (dpi->buf);
	  dpi->buf = NULL;
	  dpi->allocation_failure = 1;
	  return;
	}
      dpi->buf = newbuf;
      dpi->alc = newalc;
    }
}