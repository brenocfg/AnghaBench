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
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
struct mx_hostentry {int /*<<< orphan*/  addr; int /*<<< orphan*/  host; TYPE_1__ ai; int /*<<< orphan*/  sa; int /*<<< orphan*/  pref; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
open_connection(struct mx_hostentry *h)
{
	int fd;

	syslog(LOG_INFO, "trying remote delivery to %s [%s] pref %d",
	       h->host, h->addr, h->pref);

	fd = socket(h->ai.ai_family, h->ai.ai_socktype, h->ai.ai_protocol);
	if (fd < 0) {
		syslog(LOG_INFO, "socket for %s [%s] failed: %m",
		       h->host, h->addr);
		return (-1);
	}

	if (connect(fd, (struct sockaddr *)&h->sa, h->ai.ai_addrlen) < 0) {
		syslog(LOG_INFO, "connect to %s [%s] failed: %m",
		       h->host, h->addr);
		close(fd);
		return (-1);
	}

	return (fd);
}