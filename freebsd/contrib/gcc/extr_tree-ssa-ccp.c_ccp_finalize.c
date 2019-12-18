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
 int /*<<< orphan*/  const_val ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  substitute_and_fold (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ccp_finalize (void)
{
  /* Perform substitutions based on the known constant values.  */
  substitute_and_fold (const_val, false);

  free (const_val);
}