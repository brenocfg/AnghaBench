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

/* Variables and functions */
 char* bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_minisymbol_to_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_bfd ; 
 int /*<<< orphan*/  sort_dynamic ; 
 int /*<<< orphan*/  sort_x ; 
 int /*<<< orphan*/  sort_y ; 
 int strcmp (char const*,char const*) ; 
 int strcoll (char const*,char const*) ; 

__attribute__((used)) static int
non_numeric_forward (const void *P_x, const void *P_y)
{
  asymbol *x, *y;
  const char *xn, *yn;

  x = bfd_minisymbol_to_symbol (sort_bfd, sort_dynamic, P_x, sort_x);
  y = bfd_minisymbol_to_symbol (sort_bfd, sort_dynamic, P_y, sort_y);
  if (x == NULL || y == NULL)
    bfd_fatal (bfd_get_filename (sort_bfd));

  xn = bfd_asymbol_name (x);
  yn = bfd_asymbol_name (y);

  if (yn == NULL)
    return xn != NULL;
  if (xn == NULL)
    return -1;

#ifdef HAVE_STRCOLL
  /* Solaris 2.5 has a bug in strcoll.
     strcoll returns invalid values when confronted with empty strings.  */
  if (*yn == '\0')
    return *xn != '\0';
  if (*xn == '\0')
    return -1;

  return strcoll (xn, yn);
#else
  return strcmp (xn, yn);
#endif
}