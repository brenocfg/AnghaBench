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
struct ghes {int flags; } ;

/* Variables and functions */
 int GHES_EXITING ; 
 int /*<<< orphan*/  ghes_add_timer (struct ghes*) ; 
 int /*<<< orphan*/  ghes_proc (struct ghes*) ; 

__attribute__((used)) static void ghes_poll_func(unsigned long data)
{
	struct ghes *ghes = (void *)data;

	ghes_proc(ghes);
	if (!(ghes->flags & GHES_EXITING))
		ghes_add_timer(ghes);
}