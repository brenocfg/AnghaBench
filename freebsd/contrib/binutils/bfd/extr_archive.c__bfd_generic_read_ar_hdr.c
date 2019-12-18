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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 void* _bfd_generic_read_ar_hdr_mag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void *
_bfd_generic_read_ar_hdr (bfd *abfd)
{
  return _bfd_generic_read_ar_hdr_mag (abfd, NULL);
}