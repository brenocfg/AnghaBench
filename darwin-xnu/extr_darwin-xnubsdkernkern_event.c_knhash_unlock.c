#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* proc_t ;
struct TYPE_5__ {TYPE_1__* p_fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd_knhashlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
knhash_unlock(proc_t p)
{
	lck_mtx_unlock(&p->p_fd->fd_knhashlock);
}