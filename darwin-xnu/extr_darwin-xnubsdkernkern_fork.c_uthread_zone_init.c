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
struct uthread {int dummy; } ;

/* Variables and functions */
 int THREAD_CHUNK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  rethrottle_lock_attr ; 
 int /*<<< orphan*/  rethrottle_lock_grp ; 
 int /*<<< orphan*/  rethrottle_lock_grp_attr ; 
 int thread_max ; 
 int /*<<< orphan*/ * uthread_zone ; 
 int /*<<< orphan*/ * zinit (int,int,int,char*) ; 

__attribute__((used)) static void
uthread_zone_init(void)
{
	assert(uthread_zone == NULL);

	rethrottle_lock_grp_attr = lck_grp_attr_alloc_init();
	rethrottle_lock_grp = lck_grp_alloc_init("rethrottle", rethrottle_lock_grp_attr);
	rethrottle_lock_attr = lck_attr_alloc_init();

	uthread_zone = zinit(sizeof(struct uthread),
	                     thread_max * sizeof(struct uthread),
	                     THREAD_CHUNK * sizeof(struct uthread),
	                     "uthreads");
}