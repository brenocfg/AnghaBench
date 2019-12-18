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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int inet_aton (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twarn (char*,...) ; 

__attribute__((used)) static int
mustdiallocal(int port)
{
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
    };

    int r = inet_aton("127.0.0.1", &addr.sin_addr);
    if (!r) {
        errno = EINVAL;
        twarn("inet_aton");
        exit(1);
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        twarn("socket");
        exit(1);
    }

    // Fix of the benchmarking issue on Linux. See issue #430.
    int flags = 1;
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(int))) {
        twarn("setting TCP_NODELAY on fd %d", fd);
        exit(1);
    }

    r = connect(fd, (struct sockaddr *)&addr, sizeof addr);
    if (r == -1) {
        twarn("connect");
        exit(1);
    }

    return fd;
}