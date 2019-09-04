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
struct d_print_info {scalar_t__ len; scalar_t__ alc; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_print_resize (struct d_print_info*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static void
d_print_append_buffer (struct d_print_info *dpi, const char *s, size_t l)
{
  if (dpi->buf != NULL)
    {
      if (dpi->len + l > dpi->alc)
	{
	  d_print_resize (dpi, l);
	  if (dpi->buf == NULL)
	    return;
	}

      memcpy (dpi->buf + dpi->len, s, l);
      dpi->len += l;
    }
}