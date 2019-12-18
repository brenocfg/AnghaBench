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

/* Variables and functions */
 int /*<<< orphan*/  bfd_cache_close (scalar_t__) ; 
 int /*<<< orphan*/  bfd_get_filename (scalar_t__) ; 
 scalar_t__ obfd ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void
ar_end (void)
{
  if (obfd)
    {
      bfd_cache_close (obfd);
      unlink (bfd_get_filename (obfd));
    }
}