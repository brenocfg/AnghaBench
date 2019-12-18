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
typedef  int /*<<< orphan*/  unichar ;
typedef  int rc_uint_type ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 scalar_t__ reswr_alloc (int) ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int unichar_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static rc_uint_type
unicode_to_bin (windres_bfd *wrbfd, rc_uint_type off, const unichar *str)
{
  rc_uint_type len = 0;

  if (str != NULL)
    len = unichar_len (str);

  if (wrbfd)
    {
      bfd_byte *d;
      rc_uint_type i;
      d = (bfd_byte *) reswr_alloc ( (len + 1) * sizeof (unichar));
      for (i = 0; i < len; i++)
	windres_put_16 (wrbfd, d + (i * sizeof (unichar)), str[i]);
      windres_put_16 (wrbfd, d + (len * sizeof (unichar)), 0);
      set_windres_bfd_content (wrbfd, d, off, (len + 1) * sizeof (unichar));
    }
  off += (rc_uint_type) ((len + 1) * sizeof (unichar));

  return off;
}