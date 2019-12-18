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
struct domain {int dom_flags; } ;

/* Variables and functions */
 int DOM_INITIALIZED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  kern_control_init (struct domain*) ; 
 int /*<<< orphan*/  kern_event_init (struct domain*) ; 
 struct domain* systemdomain ; 

__attribute__((used)) static void
systemdomain_init(struct domain *dp)
{
	VERIFY(!(dp->dom_flags & DOM_INITIALIZED));
	VERIFY(systemdomain == NULL);

	systemdomain = dp;

	/* add system domain built in protocol initializers here */
	kern_event_init(dp);
	kern_control_init(dp);
}