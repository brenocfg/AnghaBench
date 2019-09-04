#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 

int fileno(FILE *f)
{
	/* f->fd never changes, but the lock must be obtained and released
	 * anyway since this function cannot return while another thread
	 * holds the lock. */
	FLOCK(f);
	FUNLOCK(f);
	return f->fd;
}