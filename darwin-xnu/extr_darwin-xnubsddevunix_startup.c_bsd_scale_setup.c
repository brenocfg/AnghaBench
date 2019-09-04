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

/* Variables and functions */
 int /*<<< orphan*/  bsd_exec_setup (int) ; 
 int desiredvnodes ; 
 int hard_maxproc ; 
 int max_cached_sock_count ; 
 int maxfiles ; 
 int maxfilesperproc ; 
 int maxproc ; 
 int maxprocperuid ; 
 scalar_t__ serverperfmode ; 
 int somaxconn ; 
 int tcp_tcbhashsize ; 
 int tcp_tfo_backlog ; 
 int vnodes_sized ; 

void
bsd_scale_setup(int scale)
{
#if defined(__LP64__)
	if ((scale > 0) && (serverperfmode == 0)) {
		maxproc *= scale;
		maxprocperuid = (maxproc * 2) / 3;
		if (scale > 2) {
			maxfiles *= scale;
			maxfilesperproc = maxfiles/2;
		}
	}
	/* Apply server scaling rules */
	if ((scale >  0) && (serverperfmode !=0)) {
		maxproc = 2500 * scale;
		hard_maxproc = maxproc;
		/* no fp usage */
		maxprocperuid = (maxproc*3)/4;
		maxfiles = (150000 * scale);
		maxfilesperproc = maxfiles/2;
		desiredvnodes = maxfiles;
		vnodes_sized = 1;
		tcp_tfo_backlog = 100 * scale;
		if (scale > 4) {
			/* clip somaxconn at 32G level */
			somaxconn = 2048;
			/*
			 * For scale > 4 (> 32G), clip
			 * tcp_tcbhashsize to 32K
			 */
			tcp_tcbhashsize = 32 *1024;

			if (scale > 7) {
				/* clip at 64G level */
				max_cached_sock_count = 165000;
			} else {
				max_cached_sock_count = 60000 + ((scale-1) * 15000);
			}
		} else {
			somaxconn = 512*scale;
			tcp_tcbhashsize = 4*1024*scale;
			max_cached_sock_count = 60000 + ((scale-1) * 15000);
		}
	}

	if(maxproc > hard_maxproc) {
		hard_maxproc = maxproc;
	}
#endif
	bsd_exec_setup(scale);
}