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
 int /*<<< orphan*/  __mfu_register (void*,size_t,int,char const*) ; 

void
__mf_register (void *ptr, size_t sz, int type, const char *name)
{
  LOCKTH ();
  BEGIN_RECURSION_PROTECT ();
  __mfu_register (ptr, sz, type, name);
  END_RECURSION_PROTECT ();
  UNLOCKTH ();
}