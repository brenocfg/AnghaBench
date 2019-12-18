#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sctp_ulpevent {struct sctp_association* asoc; } ;
struct TYPE_6__ {struct sockaddr_in v4; } ;
struct TYPE_5__ {int /*<<< orphan*/  port; TYPE_3__ primary_addr; } ;
struct sctp_association {TYPE_2__ peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_inet_msgname (char*,int*) ; 

__attribute__((used)) static void sctp_inet_event_msgname(struct sctp_ulpevent *event, char *msgname,
				    int *addr_len)
{
	struct sockaddr_in *sin, *sinfrom;

	if (msgname) {
		struct sctp_association *asoc;

		asoc = event->asoc;
		sctp_inet_msgname(msgname, addr_len);
		sin = (struct sockaddr_in *)msgname;
		sinfrom = &asoc->peer.primary_addr.v4;
		sin->sin_port = htons(asoc->peer.port);
		sin->sin_addr.s_addr = sinfrom->sin_addr.s_addr;
	}
}