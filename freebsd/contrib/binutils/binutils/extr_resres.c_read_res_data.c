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

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,long,long,long) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  get_windres_bfd_content (int /*<<< orphan*/ *,void*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
read_res_data (windres_bfd *wrbfd, rc_uint_type *off, rc_uint_type omax, void *data,
	       rc_uint_type size)
{
  if ((off[0] + size) > omax)
    fatal ("%s: unexpected end of file %ld/%ld %ld", filename,(long) off[0],
    	   (long) omax, (long) size);
  get_windres_bfd_content (wrbfd, data, off[0], size);
  off[0] += size;
}