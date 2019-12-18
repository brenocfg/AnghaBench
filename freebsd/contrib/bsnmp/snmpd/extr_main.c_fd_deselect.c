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
struct fdesc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct fdesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_suspend (struct fdesc*) ; 
 int /*<<< orphan*/  free (struct fdesc*) ; 
 int /*<<< orphan*/  link ; 

void
fd_deselect(void *p)
{
	struct fdesc *f = p;

	LIST_REMOVE(f, link);
	fd_suspend(f);
	free(f);
}