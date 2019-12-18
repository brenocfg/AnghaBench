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
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_get_section (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_is_und_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_minisymbol_to_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int non_numeric_forward (void const*,void const*) ; 
 int /*<<< orphan*/  sort_bfd ; 
 int /*<<< orphan*/  sort_dynamic ; 
 int /*<<< orphan*/  sort_x ; 
 int /*<<< orphan*/  sort_y ; 
 scalar_t__ valueof (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
numeric_forward (const void *P_x, const void *P_y)
{
  asymbol *x, *y;
  asection *xs, *ys;

  x = bfd_minisymbol_to_symbol (sort_bfd, sort_dynamic, P_x, sort_x);
  y =  bfd_minisymbol_to_symbol (sort_bfd, sort_dynamic, P_y, sort_y);
  if (x == NULL || y == NULL)
    bfd_fatal (bfd_get_filename (sort_bfd));

  xs = bfd_get_section (x);
  ys = bfd_get_section (y);

  if (bfd_is_und_section (xs))
    {
      if (! bfd_is_und_section (ys))
	return -1;
    }
  else if (bfd_is_und_section (ys))
    return 1;
  else if (valueof (x) != valueof (y))
    return valueof (x) < valueof (y) ? -1 : 1;

  return non_numeric_forward (P_x, P_y);
}