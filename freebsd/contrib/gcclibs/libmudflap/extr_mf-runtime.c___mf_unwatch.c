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
 int /*<<< orphan*/  LOCKTH () ; 
 int /*<<< orphan*/  UNLOCKTH () ; 
 unsigned int __mf_watch_or_not (void*,size_t,int /*<<< orphan*/ ) ; 

unsigned __mf_unwatch (void *ptr, size_t sz)
{
  unsigned rc;
  LOCKTH ();
  rc = __mf_watch_or_not (ptr, sz, 0);
  UNLOCKTH ();
  return rc;
}