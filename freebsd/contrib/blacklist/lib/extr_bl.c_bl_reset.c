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
typedef  TYPE_1__* bl_t ;
struct TYPE_5__ {int b_fd; int b_connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  BL_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 

__attribute__((used)) static void
bl_reset(bl_t b, bool locked)
{
	int serrno = errno;
	if (!locked)
		BL_LOCK(b);
	close(b->b_fd);
	errno = serrno;
	b->b_fd = -1;
	b->b_connected = -1;
	if (!locked)
		BL_UNLOCK(b);
}