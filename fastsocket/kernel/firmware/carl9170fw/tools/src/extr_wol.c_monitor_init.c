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
struct sockaddr_ll {scalar_t__ sll_ifindex; int /*<<< orphan*/  sll_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ll ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ if_nametoindex (char const*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_ll*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int monitor_init(const char *ifname)
{
	struct sockaddr_ll ll;
	int monitor_sock;

	memset(&ll, 0, sizeof(ll));
	ll.sll_family = AF_PACKET;
	ll.sll_ifindex = if_nametoindex(ifname);
	if (ll.sll_ifindex == 0) {
		fprintf(stderr, "Monitor interface '%s' does not exist\n", ifname);
		return -1;
	}

	monitor_sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (monitor_sock < 0) {
		fprintf(stderr, "socket(PF_PACKET,SOCK_RAW): %s\n", strerror(errno));
		return -1;
	}

	if (bind(monitor_sock, (struct sockaddr *) &ll, sizeof(ll)) < 0) {
		fprintf(stderr, "bind(PACKET): %s\n", strerror(errno));
		close(monitor_sock);
		return -1;
	}

	return monitor_sock;
}