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
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_cache_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_last_cache ; 

bfd_boolean
bfd_cache_close_all ()
{
  bfd_boolean ret = TRUE;

  while (bfd_last_cache != NULL)
    ret &= bfd_cache_close (bfd_last_cache);

  return ret;
}