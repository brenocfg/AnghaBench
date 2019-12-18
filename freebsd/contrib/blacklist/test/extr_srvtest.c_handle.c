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
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;

/* Variables and functions */
 int SOCK_DGRAM ; 
 int accept (int,void*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  process_tcp (int) ; 
 int /*<<< orphan*/  process_udp (int) ; 

__attribute__((used)) static void
handle(int type, int sfd)
{
	struct sockaddr_storage ss;
	socklen_t alen = sizeof(ss);
	int afd;

	if (type != SOCK_DGRAM) {
		if ((afd = accept(sfd, (void *)&ss, &alen)) == -1)
			err(1, "accept");
	} else
		afd = sfd;

	/* Create child process */
	switch (fork()) {
	case -1:
		err(1, "fork");
	case 0:
		if (type == SOCK_DGRAM)
			process_udp(afd);
		else
			process_tcp(afd);
		break;
	default:
		close(afd);
		break;
	}
}