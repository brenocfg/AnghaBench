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
 int /*<<< orphan*/  BEGIN_RECURSION_PROTECT () ; 
 int /*<<< orphan*/  END_RECURSION_PROTECT () ; 
 int /*<<< orphan*/  LOCKTH () ; 
 int /*<<< orphan*/  UNLOCKTH () ; 
 int __mfu_set_options (char const*) ; 

int
__mf_set_options (const char *optstr)
{
  int rc;
  LOCKTH ();
  BEGIN_RECURSION_PROTECT ();
  rc = __mfu_set_options (optstr);
  /* XXX: It's not really that easy.  A change to a bunch of parameters
     can require updating auxiliary state or risk crashing:
     free_queue_length, crumple_zone ... */
  END_RECURSION_PROTECT ();
  UNLOCKTH ();
  return rc;
}