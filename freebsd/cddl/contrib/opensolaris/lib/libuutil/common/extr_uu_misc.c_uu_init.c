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
 int /*<<< orphan*/  pthread_atfork (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_lockup ; 
 int /*<<< orphan*/  uu_release ; 
 int /*<<< orphan*/  uu_release_child ; 

__attribute__((used)) static void
uu_init(void)
{
	(void) pthread_atfork(uu_lockup, uu_release, uu_release_child);
}