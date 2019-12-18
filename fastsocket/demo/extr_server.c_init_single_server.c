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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  uint16_t ;
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  exit_cleanup () ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int init_single_server(struct in_addr ip, uint16_t port)
{
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	int serverfd, flags, value;

	if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Unable to open socket");
		exit_cleanup();
	}

	flags = fcntl(serverfd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(serverfd, F_SETFL, flags);

	value = 1;
	if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) ==
	   -1) {
		perror("Unable to set socket reuseaddr option");
		exit_cleanup();
	}

	memset(&addr, 0, addrlen);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr = ip;

	if(bind(serverfd, (struct sockaddr *)&addr, addrlen) == -1) {
		perror("Unable to bind socket");
		exit_cleanup();
	}

	if(listen(serverfd, 8192) != 0) {
		perror("Cannot listen for client connections");
		exit_cleanup();
	}

	return serverfd;
}