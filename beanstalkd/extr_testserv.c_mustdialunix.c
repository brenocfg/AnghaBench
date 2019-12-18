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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,size_t const,char*,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twarn (char*) ; 

__attribute__((used)) static int
mustdialunix(char *socket_file)
{
    struct sockaddr_un addr;
    const size_t maxlen = sizeof(addr.sun_path);
    addr.sun_family = AF_UNIX;
    snprintf(addr.sun_path, maxlen, "%s", socket_file);

    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1) {
        twarn("socket");
        exit(1);
    }

    int r = connect(fd, (struct sockaddr *)&addr, sizeof addr);
    if (r == -1) {
        twarn("connect");
        exit(1);
    }

    return fd;
}