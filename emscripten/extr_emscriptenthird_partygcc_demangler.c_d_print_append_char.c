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
struct d_print_info {int* buf; size_t len; size_t alc; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_print_resize (struct d_print_info*,int) ; 

__attribute__((used)) static void
d_print_append_char (struct d_print_info *dpi, int c)
{
  if (dpi->buf != NULL)
    {
      if (dpi->len >= dpi->alc)
	{
	  d_print_resize (dpi, 1);
	  if (dpi->buf == NULL)
	    return;
	}

      dpi->buf[dpi->len] = c;
      ++dpi->len;
    }
}