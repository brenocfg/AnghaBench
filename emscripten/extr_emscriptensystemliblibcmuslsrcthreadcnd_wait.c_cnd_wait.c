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
typedef  int /*<<< orphan*/  mtx_t ;
typedef  int /*<<< orphan*/  cnd_t ;

/* Variables and functions */
 int cnd_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cnd_wait(cnd_t *c, mtx_t *m)
{
	/* Calling cnd_timedwait with a null pointer is an extension.
	 * It is convenient here to avoid duplication of the logic
	 * for return values. */
	return cnd_timedwait(c, m, 0);
}