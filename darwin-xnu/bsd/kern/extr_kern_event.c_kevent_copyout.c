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
typedef  int user_addr_t ;
typedef  uintptr_t uint64_t ;
typedef  uintptr_t uint32_t ;
struct user64_kevent {uintptr_t ident; int /*<<< orphan*/ * ext; void* data; scalar_t__ xflags; int /*<<< orphan*/  fflags; int /*<<< orphan*/  udata; int /*<<< orphan*/  qos; int /*<<< orphan*/  flags; int /*<<< orphan*/  filter; } ;
struct user32_kevent {uintptr_t ident; int /*<<< orphan*/ * ext; void* data; scalar_t__ xflags; int /*<<< orphan*/  fflags; int /*<<< orphan*/  udata; int /*<<< orphan*/  qos; int /*<<< orphan*/  flags; int /*<<< orphan*/  filter; } ;
struct proc {int dummy; } ;
struct kevent_qos_s {uintptr_t ident; int /*<<< orphan*/ * ext; void* data; scalar_t__ xflags; int /*<<< orphan*/  fflags; int /*<<< orphan*/  udata; int /*<<< orphan*/  qos; int /*<<< orphan*/  flags; int /*<<< orphan*/  filter; } ;
struct kevent_internal_s {uintptr_t ident; int /*<<< orphan*/ * ext; scalar_t__ data; int /*<<< orphan*/  fflags; int /*<<< orphan*/  udata; int /*<<< orphan*/  qos; int /*<<< orphan*/  flags; int /*<<< orphan*/  filter; } ;
struct kevent64_s {uintptr_t ident; int /*<<< orphan*/ * ext; void* data; scalar_t__ xflags; int /*<<< orphan*/  fflags; int /*<<< orphan*/  udata; int /*<<< orphan*/  qos; int /*<<< orphan*/  flags; int /*<<< orphan*/  filter; } ;
typedef  int /*<<< orphan*/  kev64 ;
typedef  int /*<<< orphan*/  kev32 ;
typedef  void* int64_t ;
typedef  void* int32_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 unsigned int KEVENT_FLAG_LEGACY32 ; 
 unsigned int KEVENT_FLAG_LEGACY64 ; 
 unsigned int KEVENT_FLAG_STACK_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (struct user64_kevent*,int) ; 
 int copyout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
kevent_copyout(struct kevent_internal_s *kevp, user_addr_t *addrp, struct proc *p,
		unsigned int flags)
{
	user_addr_t addr = *addrp;
	int advance;
	int error;

	/*
	 * fully initialize the differnt output event structure
	 * types from the internal kevent (and some universal
	 * defaults for fields not represented in the internal
	 * form).
	 */
	if (flags & KEVENT_FLAG_LEGACY32) {
		assert((flags & KEVENT_FLAG_STACK_EVENTS) == 0);

		if (IS_64BIT_PROCESS(p)) {
			struct user64_kevent kev64;

			advance = sizeof (kev64);
			bzero(&kev64, advance);

			/*
			 * deal with the special case of a user-supplied
			 * value of (uintptr_t)-1.
			 */
			kev64.ident = (kevp->ident == (uintptr_t)-1) ?
				(uint64_t)-1LL : (uint64_t)kevp->ident;

			kev64.filter = kevp->filter;
			kev64.flags = kevp->flags;
			kev64.fflags = kevp->fflags;
			kev64.data = (int64_t) kevp->data;
			kev64.udata = kevp->udata;
			error = copyout((caddr_t)&kev64, addr, advance);
		} else {
			struct user32_kevent kev32;

			advance = sizeof (kev32);
			bzero(&kev32, advance);
			kev32.ident = (uint32_t)kevp->ident;
			kev32.filter = kevp->filter;
			kev32.flags = kevp->flags;
			kev32.fflags = kevp->fflags;
			kev32.data = (int32_t)kevp->data;
			kev32.udata = kevp->udata;
			error = copyout((caddr_t)&kev32, addr, advance);
		}
	} else if (flags & KEVENT_FLAG_LEGACY64) {
		struct kevent64_s kev64;

		advance = sizeof (struct kevent64_s);
		if (flags & KEVENT_FLAG_STACK_EVENTS) {
			addr -= advance;
		}
		bzero(&kev64, advance);
		kev64.ident = kevp->ident;
		kev64.filter = kevp->filter;
		kev64.flags = kevp->flags;
		kev64.fflags = kevp->fflags;
		kev64.data = (int64_t) kevp->data;
		kev64.udata = kevp->udata;
		kev64.ext[0] = kevp->ext[0];
		kev64.ext[1] = kevp->ext[1];
		error = copyout((caddr_t)&kev64, addr, advance);
	} else {
		struct kevent_qos_s kevqos;

		advance = sizeof (struct kevent_qos_s);
		if (flags & KEVENT_FLAG_STACK_EVENTS) {
			addr -= advance;
		}
		bzero(&kevqos, advance);
		kevqos.ident = kevp->ident;
		kevqos.filter = kevp->filter;
		kevqos.flags = kevp->flags;
		kevqos.qos = kevp->qos;
		kevqos.udata = kevp->udata;
		kevqos.fflags = kevp->fflags;
		kevqos.xflags = 0;
		kevqos.data = (int64_t) kevp->data;
		kevqos.ext[0] = kevp->ext[0];
		kevqos.ext[1] = kevp->ext[1];
		kevqos.ext[2] = kevp->ext[2];
		kevqos.ext[3] = kevp->ext[3];
		error = copyout((caddr_t)&kevqos, addr, advance);
	}
	if (!error) {
		if (flags & KEVENT_FLAG_STACK_EVENTS)
			*addrp = addr;
		else
			*addrp = addr + advance;
	}
	return (error);
}