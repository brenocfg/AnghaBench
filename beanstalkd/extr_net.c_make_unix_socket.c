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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int set_nonblocking (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 
 size_t const strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,size_t const) ; 
 int /*<<< orphan*/  twarn (char*) ; 
 int /*<<< orphan*/  twarnx (char*) ; 
 int unlink (char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
make_unix_socket(char *path)
{
    int fd = -1, r;
    struct stat st;
    struct sockaddr_un addr;
    const size_t maxlen = sizeof(addr.sun_path) - 1; // Reserve the last position for '\0'

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    if (strlen(path) > maxlen) {
        warnx("socket path %s is too long (%ld characters), where maximum allowed is %ld",
              path, strlen(path), maxlen);
        return -1;
    }
    strncpy(addr.sun_path, path, maxlen);

    r = stat(path, &st);
    if (r == 0) {
        if (S_ISSOCK(st.st_mode)) {
            warnx("removing existing local socket to replace it");
            r = unlink(path);
            if (r == -1) {
                twarn("unlink");
                return -1;
            }
        } else {
            twarnx("another file already exists in the given path");
            return -1;
        }
    }

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1) {
        twarn("socket()");
        return -1;
    }

    r = set_nonblocking(fd);
    if (r == -1) {
        close(fd);
        return -1;
    }

    r = bind(fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un));
    if (r == -1) {
        twarn("bind()");
        close(fd);
        return -1;
    }
    if (verbose) {
        printf("bind %d %s\n", fd, path);
    }

    r = listen(fd, 1024);
    if (r == -1) {
        twarn("listen()");
        close(fd);
        return -1;
    }

    return fd;
}