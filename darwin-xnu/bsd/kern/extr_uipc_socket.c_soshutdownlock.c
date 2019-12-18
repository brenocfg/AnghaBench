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
struct socket {int so_flags; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 int SOF_CONTENT_FILTER ; 
 int cfil_sock_shutdown (struct socket*,int*) ; 
 int soshutdownlock_final (struct socket*,int) ; 

int
soshutdownlock(struct socket *so, int how)
{
	int error = 0;

#if CONTENT_FILTER
	/*
	 * A content filter may delay the actual shutdown until it
	 * has processed the pending data
	 */
	if (so->so_flags & SOF_CONTENT_FILTER) {
		error = cfil_sock_shutdown(so, &how);
		if (error == EJUSTRETURN) {
			error = 0;
			goto done;
		} else if (error != 0) {
			goto done;
		}
	}
#endif /* CONTENT_FILTER */

	error = soshutdownlock_final(so, how);

done:
	return (error);
}