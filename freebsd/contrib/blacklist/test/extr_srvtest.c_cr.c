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
typedef  scalar_t__ uint8_t ;
struct sockaddr_storage {scalar_t__ ss_len; } ;
struct sockaddr_in6 {void* sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr_in {int sin_family; void* sin_port; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
typedef  void* in_port_t ;

/* Variables and functions */
 int AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int SOCK_DGRAM ; 
 int bind (int,void const*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 void* htons (void*) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cr(int af, int type, in_port_t p)
{
	int sfd;
	struct sockaddr_storage ss;
	socklen_t slen;
	sfd = socket(af == AF_INET ? PF_INET : PF_INET6, type, 0);
	if (sfd == -1)
		err(1, "socket");

	p = htons(p);
	memset(&ss, 0, sizeof(ss));
	if (af == AF_INET) {
		struct sockaddr_in *s = (void *)&ss;
		s->sin_family = AF_INET;
		slen = sizeof(*s);
		s->sin_port = p;
	} else {
		struct sockaddr_in6 *s6 = (void *)&ss;
		s6->sin6_family = AF_INET6;
		slen = sizeof(*s6);
		s6->sin6_port = p;
	}
#ifdef HAVE_STRUCT_SOCKADDR_SA_LEN
	ss.ss_len = (uint8_t)slen;
#endif
     
	if (bind(sfd, (const void *)&ss, slen) == -1)
		err(1, "bind");

	if (type != SOCK_DGRAM)
		if (listen(sfd, 5) == -1)
			err(1, "listen");
	return sfd;
}