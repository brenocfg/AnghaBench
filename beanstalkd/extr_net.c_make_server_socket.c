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
 int SD_LISTEN_FDS_START ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int errno ; 
 int make_inet_socket (char*,char*) ; 
 int make_unix_socket (char*) ; 
 int sd_is_socket_inet (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int sd_is_socket_unix (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_listen_fds (int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  twarn (char*) ; 
 int /*<<< orphan*/  twarnx (char*) ; 

int
make_server_socket(char *host, char *port)
{
    int fd = -1, r;

    /* See if we got a listen fd from systemd. If so, all socket options etc
     * are already set, so we check that the fd is a TCP or UNIX listen socket
     * and return. */
    r = sd_listen_fds(1);
    if (r < 0) {
        twarn("sd_listen_fds");
        return -1;
    }
    if (r > 0) {
        if (r > 1) {
            twarnx("inherited more than one listen socket;"
                   " ignoring all but the first");
        }
        fd = SD_LISTEN_FDS_START;
        r = sd_is_socket_inet(fd, 0, SOCK_STREAM, 1, 0);
        if (r < 0) {
            twarn("sd_is_socket_inet");
            errno = -r;
            return -1;
        }
        if (r == 0) {
            r = sd_is_socket_unix(fd, SOCK_STREAM, 1, NULL, 0);
            if (r < 0) {
                twarn("sd_is_socket_unix");
                errno = -r;
                return -1;
            }
            if (r == 0) {
                twarnx("inherited fd is not a TCP or UNIX listening socket");
                return -1;
            }
        }
        return fd;
    }

    if (host && !strncmp(host, "unix:", 5)) {
        return make_unix_socket(&host[5]);
    } else {
        return make_inet_socket(host, port);
    }
}