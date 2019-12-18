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
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  scalar_t__ unichar ;
typedef  int rc_uint_type ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  toosmall (int /*<<< orphan*/ ) ; 
 scalar_t__ windres_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static unichar *
get_unicode (windres_bfd *wrbfd, const bfd_byte *data, rc_uint_type length,
	     rc_uint_type *retlen)
{
  rc_uint_type c, i;
  unichar *ret;

  c = 0;
  while (1)
    {
      if (length < c * 2 + 2)
	toosmall (_("null terminated unicode string"));
      if (windres_get_16 (wrbfd, data + c * 2, 2) == 0)
	break;
      ++c;
    }

  ret = (unichar *) res_alloc ((c + 1) * sizeof (unichar));

  for (i = 0; i < c; i++)
    ret[i] = windres_get_16 (wrbfd, data + i * 2, 2);
  ret[i] = 0;

  if (retlen != NULL)
    *retlen = c;

  return ret;
}