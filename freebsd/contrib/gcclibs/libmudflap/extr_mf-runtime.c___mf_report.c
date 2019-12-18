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
 int /*<<< orphan*/  __mfu_report () ; 

void
__mf_report ()
{
  LOCKTH ();
  BEGIN_RECURSION_PROTECT ();
  __mfu_report ();
  END_RECURSION_PROTECT ();
  UNLOCKTH ();
}