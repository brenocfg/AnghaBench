#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct knote {TYPE_2__* kn_fp; } ;
struct TYPE_4__ {TYPE_1__* f_fglob; } ;
struct TYPE_3__ {scalar_t__ fg_data; } ;

/* Variables and functions */
 long SO_FILT_HINT_LOCKED ; 
 int filt_soread_common (struct knote*,struct socket*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

__attribute__((used)) static int
filt_soread(struct knote *kn, long hint)
{
	struct socket *so = (struct socket *)kn->kn_fp->f_fglob->fg_data;
	int retval;

	if ((hint & SO_FILT_HINT_LOCKED) == 0)
		socket_lock(so, 1);

	retval = filt_soread_common(kn, so);

	if ((hint & SO_FILT_HINT_LOCKED) == 0)
		socket_unlock(so, 1);

	return retval;
}