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
typedef  scalar_t__ zone_t ;
typedef  int vm_size_t ;
struct pipe_garbage {int dummy; } ;
struct pipe {int dummy; } ;

/* Variables and functions */
 int PIPE_GARBAGE_QUEUE_LIMIT ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nbigpipe ; 
 int /*<<< orphan*/  pipe_garbage_lock ; 
 scalar_t__ pipe_garbage_zone ; 
 int /*<<< orphan*/  pipe_mtx_attr ; 
 int /*<<< orphan*/  pipe_mtx_grp ; 
 int /*<<< orphan*/  pipe_mtx_grp_attr ; 
 scalar_t__ pipe_zone ; 
 scalar_t__ zinit (int,int,int,char*) ; 

void
pipeinit(void)
{
	nbigpipe=0;
	vm_size_t zone_size;
 
	zone_size = 8192 * sizeof(struct pipe);
        pipe_zone = zinit(sizeof(struct pipe), zone_size, 4096, "pipe zone");


	/* allocate lock group attribute and group for pipe mutexes */
	pipe_mtx_grp_attr = lck_grp_attr_alloc_init();
	pipe_mtx_grp = lck_grp_alloc_init("pipe", pipe_mtx_grp_attr);

	/* allocate the lock attribute for pipe mutexes */
	pipe_mtx_attr = lck_attr_alloc_init();

	/*
	 * Set up garbage collection for dead pipes
	 */
	zone_size = (PIPE_GARBAGE_QUEUE_LIMIT + 20) *
	    sizeof(struct pipe_garbage);
        pipe_garbage_zone = (zone_t)zinit(sizeof(struct pipe_garbage),
	    zone_size, 4096, "pipe garbage zone");
	pipe_garbage_lock = lck_mtx_alloc_init(pipe_mtx_grp, pipe_mtx_attr);
	
}