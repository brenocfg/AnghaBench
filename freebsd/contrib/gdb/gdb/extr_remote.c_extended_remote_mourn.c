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
 int /*<<< orphan*/  extended_remote_ops ; 
 int /*<<< orphan*/  remote_mourn_1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
extended_remote_mourn (void)
{
  /* We do _not_ want to mourn the target like this; this will
     remove the extended remote target  from the target stack,
     and the next time the user says "run" it'll fail.

     FIXME: What is the right thing to do here?  */
#if 0
  remote_mourn_1 (&extended_remote_ops);
#endif
}