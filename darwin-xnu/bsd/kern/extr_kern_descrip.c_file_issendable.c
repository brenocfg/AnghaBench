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
struct fileproc {int f_type; TYPE_1__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int boolean_t ;
struct TYPE_2__ {int fg_lflags; } ;

/* Variables and functions */
#define  DTYPE_NETPOLICY 132 
#define  DTYPE_PIPE 131 
#define  DTYPE_PSXSHM 130 
#define  DTYPE_SOCKET 129 
#define  DTYPE_VNODE 128 
 int FALSE ; 
 int FG_CONFINED ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  proc_fdlock_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
file_issendable(proc_t p, struct fileproc *fp)
{
	proc_fdlock_assert(p, LCK_MTX_ASSERT_OWNED);

	switch (fp->f_type) {
	case DTYPE_VNODE:
	case DTYPE_SOCKET:
	case DTYPE_PIPE:
	case DTYPE_PSXSHM:
	case DTYPE_NETPOLICY:
		return (0 == (fp->f_fglob->fg_lflags & FG_CONFINED));
	default:
		/* DTYPE_KQUEUE, DTYPE_FSEVENTS, DTYPE_PSXSEM */
		return FALSE;
	}
}