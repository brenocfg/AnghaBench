#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long pfn; } ;
struct virtqueue {unsigned long eventfd; scalar_t__ thread; TYPE_1__ config; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int CLONE_VM ; 
 unsigned long LHREQ_EVENTFD ; 
 int SIGCHLD ; 
 scalar_t__ clone (int /*<<< orphan*/ ,char*,int,struct virtqueue*) ; 
 int /*<<< orphan*/  close (unsigned long) ; 
 int /*<<< orphan*/  do_thread ; 
 int /*<<< orphan*/  err (int,char*) ; 
 unsigned long eventfd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long getpagesize () ; 
 int /*<<< orphan*/  lguest_fd ; 
 char* malloc (int) ; 
 scalar_t__ write (int /*<<< orphan*/ ,unsigned long**,int) ; 

__attribute__((used)) static void create_thread(struct virtqueue *vq)
{
	/*
	 * Create stack for thread.  Since the stack grows upwards, we point
	 * the stack pointer to the end of this region.
	 */
	char *stack = malloc(32768);
	unsigned long args[] = { LHREQ_EVENTFD,
				 vq->config.pfn*getpagesize(), 0 };

	/* Create a zero-initialized eventfd. */
	vq->eventfd = eventfd(0, 0);
	if (vq->eventfd < 0)
		err(1, "Creating eventfd");
	args[2] = vq->eventfd;

	/*
	 * Attach an eventfd to this virtqueue: it will go off when the Guest
	 * does an LHCALL_NOTIFY for this vq.
	 */
	if (write(lguest_fd, &args, sizeof(args)) != 0)
		err(1, "Attaching eventfd");

	/*
	 * CLONE_VM: because it has to access the Guest memory, and SIGCHLD so
	 * we get a signal if it dies.
	 */
	vq->thread = clone(do_thread, stack + 32768, CLONE_VM | SIGCHLD, vq);
	if (vq->thread == (pid_t)-1)
		err(1, "Creating clone");

	/* We close our local copy now the child has it. */
	close(vq->eventfd);
}