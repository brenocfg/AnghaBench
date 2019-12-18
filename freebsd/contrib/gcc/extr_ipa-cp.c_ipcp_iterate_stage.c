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
 scalar_t__ ipcp_after_propagate () ; 
 int /*<<< orphan*/  ipcp_propagate_stage () ; 

__attribute__((used)) static void
ipcp_iterate_stage (void)
{
  ipcp_propagate_stage ();
  if (ipcp_after_propagate ())
    /* Some cvals have changed from TOP to BOTTOM.  
       This change should be propagated.  */
    ipcp_propagate_stage ();
}