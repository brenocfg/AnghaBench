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
typedef  scalar_t__ rc_uint_type ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static rc_uint_type
res_to_bin_generic (windres_bfd *wrbfd, rc_uint_type off, rc_uint_type length,
		    const bfd_byte *data)
{
  if (wrbfd && length != 0)
    set_windres_bfd_content (wrbfd, data, off, length);
  return off + (rc_uint_type) length;
}